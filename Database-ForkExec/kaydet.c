#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

      char message[128];   
      strcpy(message,""); 

       read(3, message,128);
       printf("yazilacak:%s\n",message);
       fflush(stdout);
       
      // mesajı dosyaya yaz
      
      		 int num;
   		FILE *fptr;
   		// 
   		 fptr = fopen("sonuc.txt","a+");
  		 if(fptr == NULL)
   		{
   		   printf("Dosya Acilamadi!");   
   		   exit(1);             
   		}
   		fprintf(fptr,"%s\n",message);
   		fclose(fptr);
      

    return 0;
}

