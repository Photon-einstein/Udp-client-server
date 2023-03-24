// Client side implementation of UDP client-server model
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
#include <bits/stdc++.h>
#include <string>

#define PORT     8080
#define MAXLINE 1024

int sendDataToServer(const std::string &pathCleanInput);

int main() {
  int statusUdpClient, statusReadFile;
  std::string pathInput = "./../input/input_file.csv", pathCleanOutput = "./../input/input_file_clean.csv";
  statusUdpClient = sendDataToServer(pathInput);
  if (statusUdpClient != 0) {
    std::cout<<"There was an error in the function \'receiveDataFromServer\'"<<std::endl;
  }
  return 0;
}
/******************************************************************************/
int sendDataToServer(const std::string &pathCleanInput) {
  int sockfd;
  char bufferIn[MAXLINE+10], bufferOut[MAXLINE], endConnection[35]="End Connection";
  std::string lineRead;
  std::ifstream inputFileStream(pathCleanInput, std::ios_base::in);
  struct sockaddr_in     servaddr;
  if (inputFileStream.is_open() == false) {
    std::cout<<"File \'"<<pathCleanInput<<"\' failed to be opened"<<std::endl;
    return 1;
  }
  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }
  memset(&servaddr, 0, sizeof(servaddr));
  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;
  int n, len;
  while(inputFileStream.good()) {
    std::getline(inputFileStream, lineRead);
    strcpy(bufferOut, lineRead.c_str());
    sendto(sockfd, (const char *)bufferOut, strlen(bufferOut),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    printf("Send message: \t\'%s\'\n", bufferOut);
    n = recvfrom(sockfd, (char *)bufferIn, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr, (socklen_t*)&len);
    bufferIn[n] = '\0';
    printf("\t\'%s\'\n", bufferIn);
  }
  /* end connection with server */
  sendto(sockfd, (const char *)endConnection, strlen(endConnection),
      MSG_CONFIRM, (const struct sockaddr *) &servaddr,
          sizeof(servaddr));
  printf("Send message: \t\'%s\'\n", endConnection);
  close(sockfd);
  return 0;
}
/******************************************************************************/
