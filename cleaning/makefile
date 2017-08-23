all:	GA-Symbolic-Regression.exe	clean

objects:	mkdir	-p	objects

GA-Symbolic-Regression.exe:	main.o	individual.o	utils.o	node.o	GP.o
	g++	-o	GA-Symbolic-Regression.exe	main.o	individual.o	utils.o	node.o	GP.o	-std=c++11


main.o:	./sources/main.cpp
	g++	-c	./sources/main.cpp	-std=c++11

individual.o:	./sources/individual.cpp
	g++	-c	./sources/individual.cpp	-std=c++11

utils.o:	./sources/utils.cpp
	g++	-c	./sources/utils.cpp	-std=c++11

node.o:	./sources/node.cpp
	g++	-c	./sources/node.cpp	-std=c++11

GP.o:	./sources/GP.cpp
	g++	-c	./sources/GP.cpp	-std=c++11

clean:
	rm	-f	*.o
