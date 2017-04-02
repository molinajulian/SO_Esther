#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXCOLA 10 //numero de conexiones permitidas

int main (void){

	FILE *f = fopen ("/home/utnso/workspace/Memoria/memConfig.txt", "r");
 	int *MIPUERTO;
 	fseek(f,7*sizeof(char),SEEK_SET);
 	fscanf(f, "%i" ,MIPUERTO);
 	fclose ( f );
 	

	int socketListen,socketNuevo;
	int tamanioStruct = sizeof(struct sockaddr_in);
	struct sockaddr_in miDireccion, direccionEntrante;

	if((socketListen=socket(AF_INET,SOCK_STREAM,0))==-1){  //dominio=AF_INET tipo=SOCK_STREAM protocolo=0 (predeterminado)
    	perror("socket");
	    exit(1);
	}
	miDireccion.sin_family = AF_INET;         	// Ordenación de máquina
	miDireccion.sin_port = htons(*MIPUERTO);     // short, Ordenación de la red
	miDireccion.sin_addr.s_addr = INADDR_ANY; 	// nuestra IP
	memset(&(miDireccion.sin_zero), '\0', 8); 	// Poner a cero el resto de la estructura

	if ((bind(socketListen, (struct sockaddr *)&miDireccion, tamanioStruct))== -1) { //asociar socket a puerto
    	perror("bind");
    	exit(1);
    }
	if ((listen(socketListen, MAXCOLA)) == -1) { 	// abrir cola de espera de conexiones entrantes
    	perror("listen");
    	exit(1);
    }
    while(1){
		if ((socketNuevo = accept(socketListen, (struct sockaddr *)&direccionEntrante, &tamanioStruct)) == -1) { // crear nuevo socket para la conexion entrante
			perror("accept");
    		continue;}
    	printf("server: got connection from %s\n", inet_ntoa(direccionEntrante.sin_addr));
        
     
    }


}