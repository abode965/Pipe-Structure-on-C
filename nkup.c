#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
      int s;
      read(3, &s, sizeof(int));
      int sonuc= s*s*s;
      write(4, &sonuc, sizeof(int));

    return 0;
}

