/*
    Mateus Talzzia Diogo,                                     	15147861
    Paulo Vinicius Martimiano de Oliveira,             	        15149313
    Rafael Mont’Alverne de Souza,                         	15078371


*/


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
   int sockfd = 0;
    int numrv;
	char nome[20];

    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
        
	//system("python BMPtoCSV1.py");
	//system("python csvToVec2.py");

	/* Open the file that we wish to transfer */
        FILE *fp = fopen("verificarId.BMP","rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   
	long sz;
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	 if (send(sockfd, &sz, sizeof(sz), 0) < 0)
	{
	    perror("Send()");
	    exit(7);
	}

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            //printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                //printf("Sending \n");
		 if (send(sockfd, buff, nread, 0) < 0)
		{
		    perror("Send()");
		    exit(7);
		}
               // write(sockfd, buff, nread);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("Arquivo enviado...\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }


	

	fclose(fp);

	printf("Verificando...\n");
	fflush(stdout);
	if (recv(sockfd, &nome, sizeof(nome), 0) < 0)
	    {
		perror("Recv()");
		exit(6);
	    }

	if(strcmp(nome,"Negado")==0)
	{
		printf("Acesso %s",nome);
		fflush(stdout);
	}
	else
	{
		printf("Autorizado %s",nome);
		fflush(stdout);
	}



    close(sockfd);
    return 0;
}
