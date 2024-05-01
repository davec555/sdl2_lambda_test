//CC = ppc-amigaos-g++ -athread=native -Wall
CC = g++ -Wall

all: example02_lambda.o log.o config.o kbshortcuts.o
	$(CC) -o example02_lambda example02_lambda.o log.o config.o kbshortcuts.o -lSDL2 -lGLU -lGL -lpthread

lambda:
	$(CC) -c lambda.cpp -o lambda -lpthread

example02_lambda.o: example02_lambda.cpp kbshortcuts.h
	$(CC) -c example02_lambda.cpp -o example02_lambda.o

log.o: log.cpp log.h
	$(CC) -c log.cpp -o log.o

config.o: config.cpp config.h
	$(CC) -c config.cpp -o config.o

kbshortcuts.o: kbshortcuts.cpp kbshortcuts.h
	$(CC) -c kbshortcuts.cpp -o kbshortcuts.o

clean:
	-echo Cleaning up...
	-rm *.o
	-rm example02_lambda
	-echo Done.
	
