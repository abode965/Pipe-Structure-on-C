#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MSGSZ     128
/*
This Project was done for OS 2nd project 01-Dec-17 by @Abdulrahman Alabrash
alabrash.abd@gmail.com
*/


int stringToInt(char *s);
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


int main()
{
    int msqid;
    key_t key = 1234;
    message_buf  rbuf;
	int sayi;
	int toplam=0;
	int sayilar[100];
	int i=0 ;


    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }


    /*
     * Receive an answer of message type 1.
     */
  do
    {
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */
	
    sayi=stringToInt(rbuf.mtext);
   if(sayi!=0){
        sayilar[i]=sayi;
        i++;	
        toplam=toplam+sayi;
        int j;
	for(j=0;j!=i;j++){
	    if(j==i-1)
	        printf("%d",sayilar[j]);
	    else
	        printf("%d+",sayilar[j]);
	   }printf("\n");
   
   }
    
    } while(sayi!=0);

    printf("\nSonuc =%d\n",toplam);
    exit(0);
}

int stringToInt(char *s){
	int i=atoi(s);
	return i ; 

}
