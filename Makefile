tcc: bin
	tcc -Wall examples/basic.c -o bin/basic.exe

gcc: bin
	gcc -Wall examples/basic.c -o bin/basic.exe


bin:
	mkdir bin
