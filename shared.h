#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <list>

using namespace std ;

#define HEADER_SIZE 11

void SendAcrossNetwork(int sockfd, uint16_t type, char *str, uint8_t delay, uint32_t offset);


void display(uint16_t message_type,uint32_t offset, uint8_t delay, uint32_t data_length, char *hostip, int hs) ;

void get_ip_addr(int s) ;

extern int optionM ;
extern int shutDown ;
extern list<unsigned char *> myMem ;
extern list<FILE *> myFile ;
extern char *ipspouse ;
