all:
	gcc -o nkup  nkup.c -lm	 
	gcc -o nkupplus  nkupplus.c -lm	 	
	gcc -o islem  islem.c -lm
	gcc -o toplam  toplam.c -lm
	xterm -e "./toplam; bash" |xterm -e "./islem;bash"

