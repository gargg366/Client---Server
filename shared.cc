#include <iostream>
#include <stdio.h>
#include <string.h>
#include "shared.h"

int shutDown = 0 ;

void display(uint16_t message_type,uint32_t offset, uint8_t delay, uint32_t data_length){
	if (optionM){
		printf("\tReceived %d bytes from\n", data_length + HEADER_SIZE) ;
		printf("\tMessageType: 0x%04x\n", message_type) ;
		printf("\tOffset: 0x%08x\n", offset) ;
		printf("\tServerDelay: 0x%02x\n", delay) ;
		printf("\tDataLength: 0x%08x\n", data_length) ;
	}
}


void SendAcrossNetwork(int sockfd, uint16_t type, char *str, uint8_t delay, uint32_t offset){

	uint32_t dlength = 0 ;
	if (str != NULL)
		dlength = strlen(str) ;

	int buf_sz = HEADER_SIZE + dlength ;
	//	printf ("buf_sz %d\n", buf_sz) ;

	unsigned char *buf=(unsigned char *)malloc(buf_sz);
	memset(buf, 0, buf_sz) ;

	if (buf == NULL) { 
		printf("Malloc failed. Check your str\n") ;
		exit(0) ;
	}

	/* Fill out the 11-byte common header */

	/* MessageType is 0xfe20 */
	type = htons(type) ;
	memcpy(&buf[0], &type, 2) ;

	/* Offset is 0 */
	offset = htonl(offset) ;
	memcpy(&buf[2], &offset, 4) ;


	/* delay */
	memcpy(&buf[6], &delay, 1) ;


	/* Fill out the data field */
	if (dlength)
		strncpy((char *)&buf[HEADER_SIZE], str , dlength);

	/* DataLength is strlen("Makefile")=8 */
	dlength = htonl(dlength) ;
	memcpy(&buf[7], &dlength, 4) ;


	//	printf("-----------------------\n") ;
	for (int i=0; i < buf_sz ; i++) {
		if (shutDown){
			printf("@child: Time to move out...\n") ;
			return ;
		}
		int return_code=(int)write(sockfd, &buf[i], 1);
		if (return_code == -1){
			printf("Socket write error..\n");
			exit(0);
		}
		//		printf("Writing %02x\n", buf[i]) ;

	}
	//	printf("------------*----------\n") ;
	free(buf) ;
}
