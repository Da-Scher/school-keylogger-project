naktm: naktm.o keymap.o
	gcc -o naktm naktm.o keymap.o

naktm.o: naktm.c
	gcc -c naktm.c

keymap.o: keymap.c
	gcc -c keymap.c

clean:
	rm -f naktm naktm.o keymap.o
