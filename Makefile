
# CXX= g++-4.8
# CXX= g++-4.9
CXX= g++-5
# CXX= g++-6
CXXFLAGS= -g  -std=c++11
LDFLAGS= 
LDLIBS= -lpthread 


all: t1 t2 t3

clean:
	@rm -f t1 t2 t3 *.o core

