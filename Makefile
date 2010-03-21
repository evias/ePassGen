COMPILE_OPTS=-Wall
OUT=ePassGen

launch: build
	./bin/$(OUT)

build: mainJunk
	g++ -o bin/$(OUT) junk/main.o junk/utils.o junk/console.o

mainJunk: consoleJunk utilsJunk main.cpp
	g++ -o junk/main.o -c main.cpp

utilsJunk: includes/eVias/utils.hpp sources/eVias/utils.cpp
	g++ -o junk/utils.o -c sources/eVias/utils.cpp

consoleJunk: utilsJunk includes/eVias/console.hpp sources/eVias/console.cpp
	g++ -o junk/console.o -c sources/eVias/console.cpp

clean:
	rm -rf junk/*.o

mrpropre: clean
	rm -f bin/$(OUT)
