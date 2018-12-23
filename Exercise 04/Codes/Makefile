CXX=g++ 
CPPFLAGS=-Wall -O3 -g
COMPILE_SRC=-c
#OBJS=main.o hoshen_kopelman.o sandbox.o

all:prog

prog:main.cpp 
	$(CXX) $(CPPFLAGS) -o prog main.cpp sandbox.cpp hoshen_kopelman.cpp

#prog:$(OBJS)
#	$(CXX) $(CPPFLAGS) -o prog $(OBJS)

#main.o:main.cpp function_list.h
#	$(CXX) $(COMPILE_SRC) $(CPPFLAGS) -o main.o main.cpp

#hoshen_kopelman.o:function_list.h
#	$(CXX) $(COMPILE_SRC) $(CPPFLAGS) -o hoshen_kopelman.o hoshen_kopelman.cpp

#sandbox.o:function_list.h
#	$(CXX) $(COMPILE_SRC) $(CPPFLAGS) -o sandbox.o sandbox.cpp

clean:
	rm -f prog *.o *~ *.csv

