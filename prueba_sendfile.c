#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>

int main(){
   int entrada= open("origen.txt",O_RDONLY);
   if (entrada < 0){
       perror("open");
       return 1;
   }
   int salida= open("destino.txt",O_WRONLY|O_CREAT |O_TRUNC , 0644);
    if(salida<0){
       perror("open destino");
       close(entrada);
       return 1;
    }
   
    off_t desplazamiento=0;
    ssize_t bytes=sendfile(
        salida,entrada,&desplazamiento,1024
    );
    if(bytes <0 ){
      perror("sendfile");
      return 1;
    }
    printf("Bytes transferidos: %zd\n",bytes);

   close(entrada);
   close(salida);
   return 0;

}
