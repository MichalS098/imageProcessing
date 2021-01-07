#Zautomatyzowanie kompilacji uzywajac make'a
#wpisz w terminalu make, zostanie utworzony program o nazwie obr, ktory wlaczamy ./przetwarzanie

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Wfloat-equal   			#dodatkowe flagi dla kompilatora
LIBS = -lm															#tutaj dolaczamy biblioteki (dolaczenie biblioteki <math.h>)

all: funkcje.o opcje.o main.o
	$(CC) $(CFLAGS) funkcje.o opcje.o main.o -o obr $(LIBS)

opcje.o: opcje.c funkcje.h opcje.h 
	$(CC) $(CFLAGS) opcje.c -c -o opcje.o $(LIBS)

funkcje.o: funkcje.c funkcje.h opcje.h
	$(CC) $(CFLAGS) funkcje.c -c -o funkcje.o $(LIBS)

main.o: main.c funkcje.h opcje.h
	$(CC) $(CFLAGS) main.c -c -o main.o $(LIBS)

clean:
	rm -f *.o 

cleanall:
	rm -f *.o obr 
	