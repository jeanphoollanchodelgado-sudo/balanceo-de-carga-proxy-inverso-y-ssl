#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>


#define PUERTO 8088
#define MAX_EVENTOS 10

int main() {
  int servidor , epoll_fd;
   struct sockaddr_in direccion;
  servidor =socket(AF_INET,SOCK_STREAM,0);
   if(servidor < 0){
    perror("Error socket");
    return 1;
  }
  int opcion=1;
   setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&opcion , sizeof(opcion));
   memset(&direccion,0,sizeof(direccion));
   direccion.sin_family=AF_INET;
   direccion.sin_addr.s_addr =INADDR_ANY;
   direccion.sin_port =htons(PUERTO);

   if(bind(servidor, (struct sockaddr *)&direccion,
          sizeof(direccion))<0  ) {
     perror("Error bind");
     return 1;
   }
   if(listen(servidor,10) < 0  ) {
     perror("Error listen");
     return 1;
   }

    epoll_fd=epoll_create1(0);
    struct epoll_event evento;

    evento.events =EPOLLIN;
    evento.data.fd =servidor;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD, servidor,&evento);
    printf("Servidor C escuchando en puerto %d\n",PUERTO);

    struct epoll_event eventos [MAX_EVENTOS];
    while(1) {
      int cantidad =epoll_wait(
          epoll_fd,eventos,MAX_EVENTOS,-1
      );
       for (int i=0;i<cantidad ;i++){
           if(eventos[i].data.fd == servidor) {
              int cliente =accept(servidor,NULL , NULL);
              if(cliente >=0){
                struct epoll_event nuevo;
                nuevo.events=EPOLLIN;
                nuevo.data.fd =cliente;

                epoll_ctl(epoll_fd,EPOLL_CTL_ADD,cliente,&nuevo);
              }
            }else {
                int cliente = eventos[i].data.fd;
                char buffer[1024];
                    
                read(cliente,buffer,sizeof(buffer));
               
                const char *respuesta =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Connection : close\r'n"
                "Content-Length : 43\r\n\r\n "
                 "{\"status\":\"UP\",\"server\":\"kernel-c\"}\n";
                write(cliente,respuesta,strlen(respuesta));

                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,cliente,NULL);
               close(cliente);
               }
          }
    }



    close(epoll_fd);
    close(servidor);
    return 0 ;
}

       




