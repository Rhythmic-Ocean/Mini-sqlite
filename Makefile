CFLAGS = -c
CFLAGS1 = -o
main.o: main.c
	gcc $(CFLAGS) main.c

basics.o: basics.c
	gcc $(CFLAGS) basics.c

array_memory.o: array_memory.c
	gcc $(CFLAGS) array_memory.c

reading.o: reading.c
	gcc $(CFLAGS) reading.c

writing.o: writing.c
	gcc $(CFLAGS) writing.c

final: main.o basics.o array_memory.o reading.o writing.o
	gcc $(CFLAGS1) final main.o basics.o array_memory.o reading.o writing.o
	chmod +x final

clean:
	rm main.o basics.o final array_memory.o reading.o writing.o

all : final
