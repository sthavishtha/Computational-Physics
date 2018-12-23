CXX=g++
CPPFLAGS=-Wall -O3 -fopenmp
all:poisson
#ifdef 1
#CPPFLAGS+=-D_JACOBI
#endif
#ifdef 0
CPPFLAGS+=-D_GAUSS
#endif

poisson:poisson.cpp
	$(CXX) $(CPPFLAGS) -o poisson poisson.cpp

clean:
	rm -f poisson.o *~ error*
