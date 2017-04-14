#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <commons/config.h>


int main(){
	/* LEER CONFIGURACION
	*
	*/
	


	t_config *CFG;
	CFG = config_create("/home/utnso/tp-2017-1c-Oreo-Triple-Crema/Memoria/memoriaCFG.txt");
	char *PUERTO= config_get_string_value(CFG ,"PUERTO");
	int MARCOS= config_get_int_value(CFG ,"MARCOS");
	int MARCO_SIZE= config_get_int_value(CFG ,"MARCO_SIZE");
	int ENTRADAS_CACHE= config_get_int_value(CFG ,"ENTRADAS_CACHE");
	int CACHE_X_PROC= config_get_int_value(CFG ,"CACHE_X_PROC");
	char *REEMPLAZO_CACHE= config_get_string_value(CFG ,"REEMPLAZO_CACHE");
	int RETARDO_MEMORIA= config_get_int_value(CFG ,"RETARDO_MEMORIA");
	printf("Configuración:\nPUERTO = %s,\nMARCOS = %i,\nMARCO_SIZE = %i,\nENTRADAS_CACHE = %i,\nCACHE_X_PROC = %i,\nREEMPLAZO_CACHE = %s,\nRETARDO_MEMORIA = %i.\n"
			,PUERTO,MARCOS,MARCO_SIZE,ENTRADAS_CACHE,CACHE_X_PROC,REEMPLAZO_CACHE,RETARDO_MEMORIA);

	config_destroy(CFG);
	
	/*
	*
	*/
int bytesRecibidos,iof;
char* message=malloc(100*sizeof(char));
char *handshakeCliente="Hola soy la Memoria, queria comprar una casa en este terreno";
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		// Permite que la maquina se encargue de verificar si usamos IPv4 o IPv6
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	getaddrinfo("127.0.0.1", "7777", &hints, &serverInfo);	// Carga en serverInfo los datos de la conexion



	int serverSocket;
	int flagHandshake=1;
	serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);


	connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);



	freeaddrinfo(serverInfo);

		int enviar = 1;
	int i;

	char *messageRecv;

	messageRecv = malloc(100*(sizeof(char)));

	while(flagHandshake){bytesRecibidos=recv(serverSocket,messageRecv,100*sizeof(char),0);
	if(bytesRecibidos>0){flagHandshake=0;fflush(stdout); printf("%s\n", messageRecv);send(serverSocket, handshakeCliente, 60, 0);}
	}

	while(enviar){


		if ((bytesRecibidos=recv(serverSocket,messageRecv,100*sizeof(char),0)) == -1){

			      // llamada a recv()						perror("recv");
			      exit(-1);
						fflush(stdout);
			     	   }

	    printf("%s\n", messageRecv);


	 }

	free(message);
	free(messageRecv);


	close(serverSocket);
	return 0;


}