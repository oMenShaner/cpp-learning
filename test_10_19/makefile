./build/test: ./build/test.o
	g++ -std=c++11 -g -o ./build/test	./build/test.o

./build/test.o: test.cpp
	g++ -std=c++11 -c -o ./build/test.o test.cpp 

clean:
	rm ./build/test ./build/test.o
