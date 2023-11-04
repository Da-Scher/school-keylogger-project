naktm: naktm.o keymap.o keyboard-finder.o
	gcc -o naktm naktm.o keymap.o keyboard-finder.o

naktm.o: naktm.c
	gcc -c naktm.c

keymap.o: keymap.c
	gcc -c keymap.c

keyboard-finder.o: keyboard-finder.c
	gcc -c keyboard-finder.c

clean:
	rm -f naktm naktm.o keymap.o keyboard-finder.o
