build/naktm: build build/naktm.o build/keymap.o build/keyboard-finder.o 
	gcc -o build/naktm build/naktm.o build/keymap.o build/keyboard-finder.o

build:
	mkdir -p build

build/naktm.o: naktm.c
	gcc -c naktm.c -o build/naktm.o

build/keymap.o: keymap/keymap.c
	gcc -c keymap/keymap.c -o build/keymap.o

build/keyboard-finder.o: keyboard-finder/keyboard-finder.c
	gcc -c keyboard-finder/keyboard-finder.c -o build/keyboard-finder.o

clean:
	rm -rf build
