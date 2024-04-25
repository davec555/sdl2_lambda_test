//CC = ppc-amigaos-g++ -athread=native -Wall
CC = g++  -Wall

all: example02_lambda.o log.o config.o
	$(CC) -o example02_lambda example02_lambda.o log.o config.o -lSDL2 -lGLU -lGL -lpthread
lambda:
	$(CC) -c lambda.cpp -o lambda -lpthread

example02_lambda.o: example02_lambda.cpp
	$(CC) -c example02_lambda.cpp -o example02_lambda.o

log.o: log.cpp
	$(CC) -c log.cpp -o log.o

config.o: config.cpp
	$(CC) -c config.cpp -o config.o

clean:
	-echo Cleaning up...
	-rm *.o
	-rm example02_lambda
	-echo Done.
	
