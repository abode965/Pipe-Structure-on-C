#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGSZ     128 

/*
This Project was done for OS 2nd project 01-Dec-17 by @Abdulrahman Alabrash
alabrash.abd@gmail.com
*/
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
    int c; //execu değeri 
    
	//namedPipe varibles
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key=1234;
    message_buf sbuf;
    size_t buf_length;
	int k = 0; 
	

    if (pipe(pipefd) < 0) {
		perror("pipe");
        exit(1);
      }

    int sayi; //n
    printf("Sayi = ");
    scanf("%d",&sayi);
    printf("K = ");
    scanf("%d",&k);
  
    while(k!=0){
		//n^3 fork pipe kullanarak hesaplamak 
		pid = fork();
		if (pid == 0) {
			write(pipefd[1], &sayi, sizeof(int)); //n değeri gönderiliyor
            c = execv("nkup", NULL);
            perror("");
            close(pipefd[1]);
        }else {
			wait(&c);
            read(pipefd[0], &sonuc, sizeof(int));//n^3 değeri sonuc değişkene atılmak
            printf("%d \^ 3 = %d\n",sayi,sonuc);
         }
		
		//n^3+n fork pipe kullanarak hesaplamak 
        pid=fork();
		if (pid == 0) {
			write(pipefd[1], &sonuc, sizeof(int));
			c = execv("nkupplus", NULL);//n^3 değeri gönderiliyor
            perror("");
            close(pipefd[1]);
        }else {
			wait(&c);
			int sonuc2;
			read(pipefd[0], &sonuc2, sizeof(int));//n^3+n değeri sonuc2 değişkene atılmak
			printf("%d \^ 3 +%d = %d\n",sayi,sayi,sonuc2);
			
			if ((msqid = msgget(key, msgflg )) < 0) {
                perror("msgget");
                exit(1);
           }
		   
		   //named pipe işlemi başlangıcı
		   sbuf.mtype = 1;
	       char text[10];
           sprintf(text,"%d",sonuc2);//sprintf Integer String'e çevirmek için kullanılır. n^3+n değeri stringe çevirdik 
           (void) strcpy(sbuf.mtext, text);
           fflush(stdout);
           buf_length = strlen(sbuf.mtext) + 1 ;


			//Mesaje gönderme işlemi
           if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {//burada daha önce hesaplanan n^3+n toplam sınıfa namedPipe vastasıyla gönderiliyor
			   printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext,buf_length);
               perror("msgsnd");
               exit(1);
             }else
				 printf("Message: \"%s\" Sent\n", sbuf.mtext);
    
            fflush(stdout);

       
	}//if end 
	sayi++; //n++
	k--; 
	
      } //while end  
	  (void) strcpy(sbuf.mtext, "0");  
      msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT);//işlemi sonlandırmak için 0 gönderiliyor
	  return 0;
  }

char *convert(int number) //integer String e çevirmek
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

