/*
    Mateus Talzzia Diogo,                                     	15147861
    Paulo Vinicius Martimiano de Oliveira,             	        15149313
    Rafael Mont’Alverne de Souza,                         	15078371


*/


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


  typedef struct {
    char nome[20];
  }
nome;

int main(int argc, char * argv[]) {
  int listenfd = 0;
  int connfd = 0;
  int bytesReceived = 0;
  char recvBuff[256];
  char buf[2000];
  nome autorizados[10];
  int i;
  int namelen;
  long sz;
  int found = 0;
  struct sockaddr_in client;
  struct sockaddr_in serv_addr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  printf("Servidor iniciado com sucesso...\n");

  memset( & serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  if (bind(listenfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
    perror("Bind()");
    exit(3);
  }

  if (listen(listenfd, 10) == -1) {
    printf("Failed to listen\n");
    return -1;
  }

  FILE * aut;
  aut = fopen("autorizados.txt", "r");

  for (i = 0; i < 10; i++) {
    if (fgets(autorizados[i].nome, sizeof(autorizados), aut) == NULL) {
      break;
    }
    //printf("%s",autorizados[i].nome);
  }
  fclose(aut);

  do {
    namelen = sizeof(client);
    connfd = accept(listenfd, (struct sockaddr * ) & client, & namelen);

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, & (client.sin_addr), str, INET_ADDRSTRLEN);
    printf("IP do cliente conectado: %s\n", str);

    printf("Porta utilizada: %d\n", ntohs(client.sin_port));

    if (recv(connfd, & sz, sizeof(sz), 0) < 0) {
      perror("Recv()");
      exit(6);
    }

    FILE * fp;

    fp = fopen("unknown_people/verificarId_Rcv.bmp", "wb");
    if (NULL == fp) {
      printf("Error opening file");
      return 1;
    }

    /* Receive data in chunks of 256 bytes */
    long total = 0;
    while (total < sz && (bytesReceived = read(connfd, recvBuff, 256)) > 0) {
      //printf("Bytes received %d\n",bytesReceived);    
      total += bytesReceived;
      fwrite(recvBuff, 1, bytesReceived, fp);

    }

    if (bytesReceived < 0) {
      printf("Read Error/n");
    }
    fclose(fp);

    //system("pwd");
    system("cd unknown_people/ && mv verificarId_Rcv.bmp verificarId_Rcv.jpg");

    printf("Iniciando reconhecimento facial...\n");
    strcpy(buf, "face_recognition known_people/ unknown_people/");
    fp = popen(buf, "r");

    while (fgets(buf, sizeof(buf) - 1, fp) != NULL) {
      //printf("%s", buf);
    }
    //sleep(7);

    for (i = 0; i < 10; i++) {
      if (strstr(buf, autorizados[i].nome) != NULL) {
        if (send(connfd, autorizados[i].nome, strlen(autorizados[i].nome) + 1, 0) < 0) {
          perror("Send()");
          exit(7);
        }
        printf("Resposta enviada ao cliente...\n");
        found = 1;
        break;
      }

    }

    if (found == 0) {
      if (send(connfd, "Negado", sizeof("Negado"), 0) < 0) {
        perror("Send()");
        exit(7);
      }
    }

    close(connfd);
  } while (1);

  return 0;
}
