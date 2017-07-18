all:	GA-Symbolic-Regression.exe

GA-Symbolic-Regression.exe:	main.o	individual.o	utils.o	node.o	GP.o
	g++	-o	GA-Symbolic-Regression.exe	main.o	individual.o	utils.o	node.o	GP.o	-std=c++11

main.o:	main.cpp
	g++	-c	main.cpp	-std=c++11

individual.o:	individual.cpp
	g++	-c	individual.cpp	-std=c++11

utils.o:	utils.cpp
	g++	-c	utils.cpp	-std=c++11

node.o:	node.cpp
	g++	-c	node.cpp	-std=c++11

GP.o:	GP.cpp
	g++	-c	GP.cpp	-std=c++11
