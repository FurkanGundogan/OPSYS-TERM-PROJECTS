#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>

pthread_mutex_t locksum;
pthread_mutex_t lockcreator;
pthread_mutex_t lockscan;

pthread_t th_matrix_sum;
pthread_t th_matrix_creator;
pthread_t th_scan;
int toplam;
int matrix[20][20];
int matrixadet=1;

void cntl_c_handler(int dummy){
	// ctrl c ile tetiklenip programı kapatan fonksiyonu cagirir.
	signal(SIGINT,cntl_c_handler);
	printf("\n");	
	kapat();
}

void kapat(){
// tüm thredleri temizleyerek programı kapatır.
	pthread_cancel(th_matrix_creator);
	pthread_cancel(th_matrix_sum);	
	pthread_cancel(th_scan);		
	pthread_mutex_destroy(&lockcreator); 
	pthread_mutex_destroy(&locksum); 
	pthread_mutex_destroy(&lockscan); 
	printf("Threadler Sonlandirildi ve Cikis Yapildi...\n");
	exit(1);
}



void *matrixToplaveYaz(int arguman)
{	
// oluşan her matrisi toplayan thread.
	while(1){
		
		
	int i=0;
	int k=0;
	int t=0;
	for(i=0; i<matrixadet; i++)
	{
		pthread_mutex_lock(&locksum);
		
		toplam=0;
		for(k=0; k<20; k++){
				for(t=0; t<20; t++){
					
					toplam+=matrix[k][t];
				}				
			}
			printf("%d. Matrix Total:%d\n",(i+1),toplam);
			printf("---------------------------------------\n");
		
		if(i!=matrixadet-1){
		// son matrisi yazdırdıktan sonra creator yerine scan'i unlock ediyorum.
		pthread_mutex_unlock(&lockcreator);
		}else{pthread_mutex_unlock(&lockscan);}
	}
	
	
	

	
	}
	return 0;
			
}

void *matrixOlusturveYaz(int arguman) 
{		
// gelen adet sayısına göre matrix oluşturacan thread
	while(1){
		
	int i=0;
	int j=0;
	int k=0;
	int t=0;
		for(j=0; j<matrixadet; j++){	
		pthread_mutex_lock(&lockcreator);
		
		printf("\n***%d.Matrix***\n\n",(j+1));				
			for(k=0; k<20; k++){
				for(t=0; t<20; t++){
					int top=99;
					int number=0;
					number=(rand())%top;
					matrix[k][t]=number;
					printf("%d ",matrix[k][t]);
				}
				printf("\n");
			}
			printf("\n");
		pthread_mutex_unlock(&locksum);	
			
		}
		
		
					
	}
	return 0;
}
void *adetAl(){
// kullanıcıdan sürekli adet isteyen thread.
	while(1){
	
	pthread_mutex_lock(&lockscan);
	
	matrixadet=1;
	toplam=0;
	// Kullanıcı girişi <=0 olana kadar uygulama çalışıyor.
		printf("\nMatrix Adedi Giriniz:");
		srand(time(0));		
		if(!(scanf("%d",&matrixadet)))matrixadet=0;
		// scanf ile alınan deger sayi degilse matrixadet=0 oluyor dolayısıyla
		// program alttaki koşula girerek sonlanıyor.
				
		if(matrixadet<=0){
			
			pthread_cancel(th_matrix_creator);
			pthread_cancel(th_matrix_sum);	
			pthread_mutex_destroy(&lockcreator); 
			pthread_mutex_destroy(&locksum); 
			pthread_mutex_destroy(&lockscan); 
			printf("Threadler Sonlandirildi ve Cikis Yapildi...\n");
			exit(1);
			//kapat();
			// burada th_scan'i cancel edemedim e kapat çalışmıyordu.
			// bu sebeple onu cancel edemeden exit yaptım.
			
		}	
		printf("\n[%d Adet Matrix Olusturuluyor]\n\n",matrixadet);
		
		pthread_mutex_unlock(&lockcreator);
	}
	return 0;
}


int main(){	
	signal(SIGINT,cntl_c_handler);
	
	
	pthread_mutex_init(&locksum, NULL);
	pthread_mutex_init(&lockcreator, NULL);
	pthread_mutex_init(&lockscan, NULL);
	
	pthread_mutex_lock(&locksum);
	pthread_mutex_lock(&lockcreator);

	
	
	
	void* status;
	pthread_create(&th_scan,NULL,adetAl,NULL);
    	pthread_create(&th_matrix_sum,NULL,matrixToplaveYaz,matrixadet);
    	pthread_create(&th_matrix_creator,NULL,matrixOlusturveYaz,matrixadet);  	
    	  
    		
	pthread_join(th_matrix_sum,&status);
	pthread_join(th_matrix_creator,&status);	
	pthread_join(th_scan,&status);
	
	
	
	
	return 0;
}

