#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char komutlarim[4][10]={
    				"tekrar","islem","cat","clear"
};
char input[250];
int control=0;
int cokluFonkMu=0;
char**envp2;

int standartCalisma(char input[]){
char temp[250];
strcpy(temp,input);
char * parca=strtok(temp," ");
int komut=0;
for(int i=0;i<4;i++){
   // girilen komutun komutlarim listesinde olup olmamasini kontrol ediyor.
    if(strcmp(parca,komutlarim[i])==0){
    // inputun komut dizisinde var ise control 1 oluyor.      
    control=1;
    komut=i;
    break;
    }  
 }
 
if(control==1){	
        // komut var ise komutun id'sine göre fonksiyon çağırıyoruz.
	if(komut==0){
	tekrarKomutuCalis(input);
	}else if(komut==1){
	islemKomutuCalis(input);
	}else if(komut==2){
	catCalis(input);
	}else if(komut==3){
	clearCalis();
	}


}else{
printf("Komut Bulunamadi!!!\n");
} 
return 0;
}


int islemKomutuCalis(char input[]){
char temp[250];
strcpy(temp,input);
int adet=0;

char * parca=strtok(temp," ");
while(parca!=NULL){
parca=strtok(NULL," ");
adet++;
}
// İşlem fonksiyonu için parametre sayısı 4 değilse hata yazdırıyoruz.
if(adet!=4){printf("Parametre Hatasi\n");}else{
	// Dört parametreyi de bir diziye atıyoruz.
	char *parametreler2[5];
	int i=0;
	char temp2[50];
	strcpy(temp2,input);
	char * parca2=strtok(temp2," ");
	while(parca2!=NULL){
	parametreler2[i]=parca2;
	i++;
	parca2=strtok(NULL," ");
	}
	parametreler2[4]=NULL;

	// Son iki parametrenin sayı olup olmamasını kontrol ediyorum.
	if(strtoint(parametreler2[2])!=-1 && strtoint(parametreler2[3])!=-1){	
	
	// Diğer parametrelerde sıkıntı yoksa 2.parametreye ait fonksion  
	// çağırılıyor.				
     	int t;
     	int f;
        f= fork();
      if(f==0)
      {                        
          t = execve("islem",parametreler2,envp2);
          perror("exec: execve failed\n");
      }
      else
      {
          int cpid = wait(&t); // forku bekle      
        if(WEXITSTATUS(t)!=NULL){
        // Bu noktada yaşadığım hata. İşlem sonucu 0 ise sanki null mış gibi else'e geçiyor.
       
        // islem.c den dönen degeri alip sonucu yazdiriyoruz.
        int sonuc=WEXITSTATUS(t);
        char islem='+';
              if(strcmp(parametreler2[1],"cikar")==0)islem='-';
        printf("%s %c %s = %d\n",parametreler2[2],islem,parametreler2[3],sonuc);
        printf("***Matamatik işlemi bitti***\n");
        }else{
        // sonuc NULL(0) dönüyorsa 2. parametre (fonksiyon adi) hatalidir.
        printf("Parametre Hatasi\n");
        
        }
         
         
      }
      
	}
	else{	
        // Son iki parametre sayı değilse hata yazdırıyoruz.
	printf("Parametre Hatasi!!!\n");
	
	}

}

return 0;
}


int tekrarKomutuCalis(char input[]){
char temp[250];
strcpy(temp,input);
int adet=0;

char * parca=strtok(temp," ");
while(parca!=NULL){
parca=strtok(NULL," ");
adet++;
}
// Tekrar fonksiyonu için parametre sayısı 3 değilse hata yazdırıyoruz.
if(adet!=3){printf("Parametre Hatasi\n");}
else{
// Eğer tam 3 parametre varsa bunları dizimize atıyoruz.
char *parametreler[4];
int i=0;
char temp2[50];
strcpy(temp2,input);
char * parca2=strtok(temp2," ");
while(parca2!=NULL){
parametreler[i]=parca2;
i++;
parca2=strtok(NULL," ");
}
parametreler[3]=NULL;
// Son kontrol olarak 'tekrar fsm 3' gibi bir fonksiyon için 3. parametrenin... 
// Sayı olup olmamasını kontrol ediyoruz. Bir sayı değilse hata verdiriyoruz.
if(strtoint(parametreler[2])==-1){printf("Parametre Hatasi!!!\n");}
else{
// Hatasız bir şekilde çağırıldıysa tekrar fonksiyonunu işleme geçiriyoruz.
     int t;
     int f;
      f= fork();
      if(f==0)
      {
         // printf("Ana program: Exec calisti\n");        
          t = execve("tekrar",parametreler,envp2);
          perror("exec: execve failed\n");
      }
      else
      {
          int cpid = wait(&t); // forku bekle
        //  printf("Ana program: alt program bitirdi?\n");
        //  printf("Main2'den donen toplam: %d\n",WEXITSTATUS(t));
          
      }
}
return 0;
}
}


int catCalis(char input[]){
char temp[250];
strcpy(temp,input);

char *parametreler[3];
int i=0;
char * parca=strtok(temp," ");
while(parca!=NULL){
parametreler[i]=parca;
i++;
parca=strtok(NULL," ");
}
parametreler[2]=NULL;
     int t;
     int f;
      f= fork();
      if(f==0)
      {                 
          t = execve("/bin/cat",parametreler,envp2);
          perror("exec: execve failed\n");
      }
      else
      {
          int cpid = wait(&t); // forku bekle               
      }

}

int clearCalis(){
// bin altındaki cleari cagirdim.
// parametre olarak clear göndermem gerekiyordu
// bir dizi oluşturup parametreyi gönderdim.
char *parametreler[2];
parametreler[0]="clear";
parametreler[1]=NULL;
     int t;
     int f;
      f= fork();
      if(f==0)
      {                 
          t = execve("/bin/clear",parametreler,envp2);
          perror("exec: execve failed\n");
      }
      else
      {
          int cpid = wait(&t); // forku bekle               
      }
}

int main(int argc, char *argv[],char ** envp)
{

envp2=envp;

while(1){
    // sürekli komut bekliyoruz.
    control=0;
    cokluFonkMu=0;
    printf("myshell>> ") ;
    gets(input);
    for(int i=0;i<strlen(input);i++){
    // komut satırında | var ise farklı çalışacağı için bir kontrol koydum.
    if(input[i]=='|'){
    cokluFonkMu=1;
    		}   
	}

    if(cokluFonkMu==0){
    // eğer tek bir fonksiyon çağırıldıysa buradan devam ediyoruz.
    char temp[250];
    strcpy(temp,input);
    char * parca=strtok(temp," ");
    // Komut satırından girilen değerlerin ilk parçasının exit olup olmamasına
    // göre çıkış yapıyoruz.
    if(strcmp(parca,"exit")==0){printf("Cikis Yapildi..\n.");return 0;}else{
    }
    
    // Komut satırından tek bir 'tekrar' ya da 'işlem' fonksiyonu 
    // çalıştırmak için standartCalisma fonksiyonunu oluşturdum.
    standartCalisma(input);
    
    } else {
    // Çoklu fonksiyon çalıştırma
    
    // gelen komutları | ya göre ayırıp diziye atıyor.
    		char temp[250];
		strcpy(temp,input);
		char *cokluKomutlar[11];
		int i=0;
		char * parca=strtok(temp,"|");
		while(parca!=NULL){
		cokluKomutlar[i]=parca;
		i++;
		parca=strtok(NULL,"|");
		}
		cokluKomutlar[10]=NULL;		
				
		printf("%d Komut var :\n",i);
		// sıralı gelmiş tüm komutları çağırıyor.
		for(int t=0;t<i;t++){
		standartCalisma(cokluKomutlar[t]);
		}
		
				
    		printf("---Çoklu işlem bitmiştir---\n");
    }   
    
    }
    return 0;
}


int strtoint( char* charnums)
{
 int number=0;
 int index=0;
 while(charnums[index])
 {
    if(('0'<=charnums[index]) && (charnums[index]<='9'))
    {

    if(!number)
        number= ( (int) charnums[index]) - 48;
    else
    {
        number = (number *= 10) + ((int) charnums[index] - 48);
    }
    index++;
         }
         else
         {
            number=-1;           
            break;
         }
 }
 return number;
}

