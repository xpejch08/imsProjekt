CC=g++
CPPFLAGS=-Wextra -pedantic -Wall -O2 -std=c++11 -g
LDFLAGS=-lsimlib -lm

all: ims

ims:
	$(CC) $(CPPFLAGS) -o ims main.cpp $(LDFLAGS)

run:
	./ims exp1

run2:
	./ims exp2

run3:
	./ims exp3

run4:
	./ims exp4

run5:
	./ims exp5

plot:
	gnuplot population.plt

clean:
	rm -f ims ./*.out
	rm -f *.dat
	rm -f *.png