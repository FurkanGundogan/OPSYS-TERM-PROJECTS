#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>


#define MSGSZ     128


/*
 * Declare the message structure.
 */

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


main()
{

    int msqid;
    key_t key;
    int msgflg = IPC_CREAT | 0666;
    message_buf  rbuf;
    message_buf  sbuf;
     size_t buf_length;
     char * srg[100];
    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1234;

    if ((msqid = msgget(key, msgflg)) < 0) {
        perror("msgget");
        exit(1);
    }

   while(1){

   	   printf("Sorgu Giriniz: ");
   	   fflush(stdout);
   	   
   	   gets(srg);
   	   if(strcmp(srg,"exit")==0)break;
   	   fflush(stdout);  	   
   	   strcpy(sbuf.mtext, srg);
   	   sbuf.mtype = 1;
    	   buf_length = strlen(sbuf.mtext) + 1 ;
	   if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {

		perror("msgsnd");
		exit(1);
	   }
	   
	   
	   if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
              perror("msgrcv");
              exit(1);
	   }
	   // sonuctan donen degeri programa yazdırıyoruz
 	   printf("Sonuc= %s\n",rbuf.mtext);
 	   if(strcmp(rbuf.mtext,"null")==0){
 	   // boş donduyse kayit bulunamadi hatası veriyoruz ve 
 	   //program yeni sorgu almaya çalışmaya devam ediyor.
 	   	printf("Kayit Bulunamadi\n");
 	   }else {
 	   
 	   // Kayıt geldiği taktirde kayıt edilip edilmeyeceğini soruyoruz ve bir input bekliyoruz.
 	   	printf("Sorgu sonucu kaydedilsin mi? e/h :\n");
 	   	
 	   	char cevap[1];
 	   	strcpy(cevap,"");
 	   	gets(cevap);
 	   	
 	   	if(strcmp(cevap,"e")==0){
 	   		// Cevap "e" ise kayıt işlemini pipe ile yapıyoruz.
 	   			 	   		   
    			  //pipe olustur
    			   int pipefd[2];
 			   int c;
    			  if (pipe(pipefd) < 0) {
     			   perror("pipe 2 olusturulamadi");
     				   exit(1);
     			  }
     			  int pid = fork();     			 
     			  if (pid == 0) {    			  
   	     	  		//pipe'a db'den gelen sonucu yazıyoruz..    	  		
       		   	write(4, rbuf.mtext,128); 
        		  	 // programi cagir
         		  	 c = execv("kaydet", NULL);       		  	 
         			  // hata olusursa
         		  	 perror("");
       		   	 close(pipefd[1]);
     			  }else {  
     			          int cpid = wait(&c);      			         
      			          printf("Kayıt Tamamlandi.\n");
       		 	 		  
        			}
        			 
          
 	   			   		
 	   		//printf("Kayıt Yapıldı\n");
 	   	}else{
 	   		printf("Kayıt işlemi yapılmadı.\n");
 	   	}
 	   	
 	   }
   	
    } 

    printf("Program Bitti...\n");
    exit(0);
}
