//CC = ppc-amigaos-g++ -std=c++11 -athread=native -Wall
CC = g++  -Wall 

all:
	$(CC) example02_lambda.cpp -o example02_lambda -lSDL2 -lGLU -lGL -lpthread
lambda:
	$(CC) lambda.cpp -o lambda -lpthread
clean:
	@echo Cleaning up...
	@rm lesson04
	@echo Done.