#include <iostream>
#include <cstdio>

#include "BinaryTree.hpp"

using namespace std;

const int pop_size = 20;
const int pop_deepth = 10;

const double mutation_rate = 0.01;

int main() {

	population *pop = new population(pop_size);

	pop->print_pop();
	
	for (int i=0; i<pop_size; i++) {
		cout << "resultado da operação do individuo " << i 
						<< ": " <<  pop->pop[i]->recupera_valor() << endl ;
	}
	
  	delete pop;
		
	return 0;
}
