all:	hk

hk:	call.cpp
	g++ -std=c++11 -g -Wall -O3 -fopenmp call.cpp hoshen_kopelman.cpp -o hk

clean:
	rm -f hk

.PHONY:	all clean
