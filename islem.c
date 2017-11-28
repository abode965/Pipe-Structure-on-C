#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ     128 

char *convert(int number);

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;




main()
{
      int pipefd[2];
      int pid;
      int i, line, sonuc;
      char s[1000];
      int c;
    //namedPipe varibles
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key=1234;
    message_buf sbuf;
    size_t buf_length;
	int k = 5;

      if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
      }

      int sayi;
      printf("Sayi = ");
      scanf("%d",&sayi);
    while(k!=0){      
      pid = fork();

      if (pid == 0) {
         
          write(pipefd[1], &sayi, sizeof(int));
          c = execv("nkup", NULL);
          perror("");
          close(pipefd[1]);
      } else {

         wait(&c);
         read(pipefd[0], &sonuc, sizeof(int));
         printf("%d \^ 3 = %d\n",sayi,sonuc);
         }
        pid=fork();
	if (pid == 0) {
         write(pipefd[1], &sonuc, sizeof(int));
          c = execv("nkupplus", NULL);
          perror("");
          close(pipefd[1]);
        }else {
	 wait(&c);
	 int sonuc2;
	 read(pipefd[0], &sonuc2, sizeof(int));
	 printf("%d \^ 3 +%d = %d\n",sayi,sayi,sonuc2);
        
          if ((msqid = msgget(key, msgflg )) < 0) {
                perror("msgget");
                exit(1);
           }
       
             sbuf.mtype = 1;
	     char text[10];
             sprintf(text,"%d",sonuc2);//Integer to String 
            (void) strcpy(sbuf.mtext, text);
             fflush(stdout);
             buf_length = strlen(sbuf.mtext) + 1 ;


    /*
     * Send a message.
     */
            if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
                 printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext,buf_length);
                 perror("msgsnd");
                 exit(1);
             }else
                 printf("Message: \"%s\" Sent\n", sbuf.mtext);
    
            fflush(stdout);

       
	}sayi++;k--;
	
      } //while end  
	(void) strcpy(sbuf.mtext, "0");//end the other class by sending 0 
       msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT);
        
 
      return 0;
  }

char *convert(int number)
{
    int count=0;
    int numbertmp=number;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        count++;
    }
    char * value= (char * ) calloc (count,sizeof(unsigned char)  );
    numbertmp=number;
    count--;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        char x=(char) 48+digit;
        *(value+count)=x;
        count--;
    }

    return value;
}

