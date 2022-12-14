
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#define PORT     8080
#define MAXLINE 1024


/* this function send the clean data into the client and in the end it returns
0 if no error or other value if error */
int receiveDataFromClient();

int main() {
  int statusUdpServer, statusReadFile;
  std::string pathInput = "./../input/input_file.csv", pathCleanOutput = "./../input/input_file_clean.csv";
  statusUdpServer = receiveDataFromClient();
  return 0;
}
/******************************************************************************/
int receiveDataFromClient() {
  int sockfd;
  char bufferIn[MAXLINE], bufferOut[MAXLINE+24];
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if ( bind(sockfd, (const struct sockaddr *)&servaddr,
          sizeof(servaddr)) < 0 )
  {
      perror("bind failed");
      exit(EXIT_FAILURE);
  }

  int len, n;

  len = sizeof(cliaddr);  //len is value/result

  while(1) {
    n = recvfrom(sockfd, (char *)bufferIn, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t*)&len);
    bufferIn[n] = '\0';
    printf("Received from Client : %s\n", bufferIn);
    sprintf(bufferOut,"OK from Server: \'%s\'", bufferIn);

    sendto(sockfd, (const char *)bufferOut, strlen(bufferOut),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    if (strcmp(bufferIn, "End Connection") == 0) {
      break;
    }
  }
  return 0;
}
/******************************************************************************/
