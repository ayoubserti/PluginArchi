all: XFile

clean: 
	rm -rf *.o

%: %.cpp
	g++ -std=c++11 -c -I../../ -I../include -D_GCC $< -o $@