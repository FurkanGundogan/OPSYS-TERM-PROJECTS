#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            printf("\nGecersiz islem");
            break;
         }
 }
 return number;
}

int main(int argc, char *argv[], char**envp2)
{  
     int sonuc=-1;
     int t;
     int f;
      f= fork();
      if(f==0)
      {
      // 2. parametre topla ya da cikar değilse program NULL(0) dönecektir.
      if( strcmp(argv[1],"topla")==0|strcmp(argv[1],"cikar")==0){
       t = execve(argv[1],argv,envp2);
       perror("exec: execve failed\n");	
 		 }else{return NULL;}
         
      }
      else
      {
          int cpid = wait(&t); // forku bekle   
          // topla/cikar 'dan dönen degeri shell'e döndürüyoruz.    
          sonuc = WEXITSTATUS(t);
      }

   return sonuc;
}
