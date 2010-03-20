COMPILE_OPTS=-Wall
OUT=ePassGen

launch: build
	./bin/$(OUT)

build: utilsJunk mainJunk
	g++ -o bin/$(OUT) junk/main.o junk/utils.o

utilsJunk: includes/eVias/utils.hpp sources/eVias/utils.cpp
	g++ -o junk/utils.o -c sources/eVias/utils.cpp

mainJunk: main.cpp utilsJunk
	g++ -o junk/main.o -c main.cpp

clean: 
	rm -rf junk/*.o

mrpropre: clean
	rm -f bin/$(OUT)
