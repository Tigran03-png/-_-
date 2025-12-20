supplies: main.c supplies.c supplies.h
	gcc main.c supplies.c -o supplies

run: supplies
	./supplies

clean:
	rm -f supplies supplies.bin
