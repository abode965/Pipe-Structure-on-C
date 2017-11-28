#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[])
{
      int s;
      read(3, &s, sizeof(int));
      int sonuc= cbrt(s)+s;
      write(4, &sonuc, sizeof(int));

    return 0;
}

