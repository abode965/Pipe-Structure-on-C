#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
This Project was done for OS 2nd project 01-Dec-17 by @Abdulrahman Alabrash
alabrash.abd@gmail.com
*/

int main(int argc, char *argv[])
{
      int s;
      read(3, &s, sizeof(int));
      int sonuc= cbrt(s)+s;//sonuç=∛n+n gelen n^3 degeri cbrt fonksiyonu kullanarak küp kök hesaplanabilir 
      write(4, &sonuc, sizeof(int));

    return 0;
}

