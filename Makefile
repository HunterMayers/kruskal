CC=g++ -Wall -Werror -W -pedantic


all: kruskals

kruskals: kruskals.cpp
	$(CC) kruskals.cpp -o kruskals

clean:
	rm kruskals
