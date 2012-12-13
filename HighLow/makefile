all: HighLow

HighLow: HighLow.o
	g++ -Wall -g -o HighLow HighLow.o

HighLow.o: HighLow.cpp
	g++ -Wall -g -c HighLow.cpp

clean:
	rm -f *.o *~ HighLow
