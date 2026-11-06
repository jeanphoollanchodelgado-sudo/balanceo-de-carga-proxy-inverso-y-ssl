#Proyecto linux server 

##Descripciomn
Implementacion de un servicio linux con proxy inverso,
balanceo de carga y componentes nativos del kernel.

## Arquitectura
 - ubuntu-proxy :NGINX Y HTTPS
 - ubuntu-backend1:servicio HTTP puerto 8080
 - ubuntu-backend2:servicio HTTP puerto 8081

## componentes

 -socket()
 -blind()
 -listen()
 -accept()
 -epoll()
 -sendfile()

##Pruebas

 -Balanceo Round RObin
 -Comunicacion entre servidores
 -HTTPS
 -Servidor C local
 -Transferencia mediante sendfile()
