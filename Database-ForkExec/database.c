#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define MSGSZ     128


/*
 * Declare the message structure.
 */

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;
         
void parseWithSpace(char *satir, char **parsed) // parse methodu
{
    int i;

    for (i = 0; i < 100; i++)
    {
        parsed[i] = strsep(&satir, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

main()
{


    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    message_buf rbuf;
    size_t buf_length;

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }


    //int sayi1=0;
    //int sayi2=0;
    int i=0;
    do
    {

	if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
              perror("msgrcv");
              exit(1);
	}
	

 	char * gelenmetin[100];
 	strcpy(gelenmetin, rbuf.mtext);	
 	printf("Gelen Sorgu: %s\n",gelenmetin);
 	
 	
 	char * sorguElemanlari[100];
 	//fflush(stdout);	
 	parseWithSpace(gelenmetin,sorguElemanlari);

 		int t=0;
 		while(sorguElemanlari[t]!=NULL){
 		printf("%d : %s\n",t,sorguElemanlari[t]);
 		t++;
 		}
 	//fflush(stdout);		
 	char sonuc[250];
 	strcpy(sonuc,"");
 	
 	// select * from veri1.txt where ad=selin
 	// dosya adina gore dosya acma
 	// * , ad , number kontrol
 	// = e göre parse 
 	char sol[20];
 	char sag[20];
 	
 	// strtok ile = in sol ve sag tarafını aldım
 	// sol tarafın "ad" ya da "number" olmasın göre işlem devam edecek
 	
 	char *ptr = strtok(sorguElemanlari[5],"=");	
 	strcpy(sol,ptr);
 	printf("sol:%s\n",sol);
 	ptr=strtok(NULL,"=");	
 	strcpy(sag,ptr);
 	printf("sag:%s\n",sag);
 	
 	// Anlamlandıramadığım bir sebeple dosyayanın ikinci satırı okunurken
 	// commandline dan girdiğim number=6 değerinin verileri dizisinden siliniyordu.
 	// ben de yedeğini alarak işlem yaptırdım.
 	char solyedek[20];
 	strcpy(solyedek,sol);
 	
 	         FILE *fp = fopen(sorguElemanlari[3], "r");
    		 if(fp == NULL) {
       	 perror("Unable to open file!");
        	 exit(1);
    		}
    		char chunk[128];
    	 	while(fgets(chunk, sizeof(chunk), fp) != NULL) {   	 	
    	 	char chunkyedek[128];
    	 	strcpy(chunkyedek,chunk);
    	 	// Eşleşme sonrasında sonuca ekleme yapmak için okunan satırı yedekledim
    	 	    	 			  	 		
    	 			char ad[20];
 				char number[20];
    	 			char *ptr2 = strtok(chunk," ");	
 				strcpy(ad,ptr2);				
 				ptr2=strtok(NULL,"");	
 				strcpy(number,ptr2);
 			//	printf("x:%s-len:%d\n",ad,strlen(ad));
 			//	printf("y:%s-len:%d\n",number,strlen(number));
 				int numLen=strlen(number);
 								
    	 			if(strcmp(solyedek,"ad")==0){
    	 				if(strcmp(sag,ad)==0){
    	 				// isim verisi eşleşiyorsa kaydı sonucumuza ekliyoruz
    	 				 	 					
    	 					// *,ad,number seçim sorgusuna göre sonuca ekleme
    	 					if(strcmp(sorguElemanlari[1],"*")==0){
    	 					strcat(sonuc,chunkyedek);
    	 					}else if (strcmp(sorguElemanlari[1],"ad")==0){
    	 					strcat(sonuc,ad);
    	 					strcat(sonuc,"\n");
    	 					}else if (strcmp(sorguElemanlari[1],"number")==0){
    	 					strcat(sonuc,number);
    	 					}
    	 				
    	 				
    	 				printf("Eslesen:%s\n",chunkyedek);
    	 				}
    	 			

    	 			} 	 			
    	 			else if(strcmp(solyedek,"number")==0){    	 			
    	 				int sayi=0;
    	 				if(numLen>3){
    	 				// dosyada sayılar örn: "6\n" olduğu için en az 3 elemanlı  	 						// len'i 3'ten büyük olanlar için sondaki boşlukları
    	 				// silerek temiz bir sayı çıkartma
    	 					int newlen=numLen-2;
    	 					char duzgunSayi[newlen];   	 				
    	 					for(int i=0;i<newlen;i++){
    	 					duzgunSayi[i]=number[i];
    	 					}
    	 					duzgunSayi[newlen]=NULL;
    	 					
    	 					if(strcmp(duzgunSayi,sag)==0){
    	 					// sayida eşleşme saglanirsa kayidi sonuca ekliyoruz.
    	 					
    	 					// *,ad,number seçim sorgusuna göre sonuca ekleme
    	 					// üst kısımdaki kodun aynısı
    	 						if(strcmp(sorguElemanlari[1],"*")==0){
    	 						strcat(sonuc,chunkyedek);
    	 						}else if (strcmp(sorguElemanlari[1],"ad")==0){
    	 						strcat(sonuc,ad);
    	 						strcat(sonuc,"\n");
    	 						}else if (strcmp(sorguElemanlari[1],"number")==0){
    	 						strcat(sonuc,number);
    	 						}
    	 					
    	 						
    	 						printf("Eslesen:%s\n",chunkyedek);
    	 					}
    	 			
    	 			
    	 				
    	 				}else{
    	 				
    	 					char sayimiz[1];
    	 					strcpy(sayimiz,"");
    	 					
    	 					strncat(sayimiz,&number[0],1);
    	 					if(strcmp(sayimiz,sag)==0){
    	 					
    	 					
    	 					// *,ad,number seçim sorgusuna göre sonuca ekleme
    	 					// üst kısımdaki kodun aynısı
    	 						if(strcmp(sorguElemanlari[1],"*")==0){
    	 						strcat(sonuc,chunkyedek);
    	 						}else if (strcmp(sorguElemanlari[1],"ad")==0){
    	 						strcat(sonuc,ad);
    	 						strcat(sonuc,"\n");
    	 						}else if (strcmp(sorguElemanlari[1],"number")==0){
    	 						strcat(sonuc,number);
    	 						}
    	 						
    	 						printf("Eslesen:%s\n",chunkyedek);
    	 						
    	 					}
    	 					
    	 				
    	 				}	
    	 			
    	 			
    	 			}
    	 			
    	 		//	printf("boy:%d\n",strlen(chunk));
    	 			
    	 			
    	 			
         	//printf("veri: %s\n",chunk); 
     		}
 
    		 fclose(fp);
        
 	//printf("Sonuc:%s-%d\n",sonuc,strlen(sonuc));
 	
 	
 	if(strlen(sonuc)==0)strcpy(sonuc,"null");
 			
   	strcpy(sbuf.mtext, sonuc);
   	sbuf.mtype = 1;
    	buf_length = strlen(sbuf.mtext) + 1 ;
	if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {

		perror("msgsnd");
		exit(1);
	}
   		
	
        } while(1);

    exit(0);
}
