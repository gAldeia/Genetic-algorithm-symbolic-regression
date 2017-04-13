#include <iostream>
#include <cstdio>

#include "BinaryTree.hpp"

using namespace std;

const int pop_size = 5;
const int pop_deepth = 10;

const double mutation_rate = 0.01;

int main() {

	population *pop = new population(pop_size);

	pop->imprime_pop();

  	delete pop;
		
	return 0;
}
