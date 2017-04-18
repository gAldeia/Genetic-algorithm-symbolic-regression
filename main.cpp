#include <iomanip>
#include <iostream>
#include <cstdio>

#include "BinaryTree.hpp"

using namespace std;

const int pop_size = 50;
const int pop_deepth = 5;

const double mutation_rate = 0.01;

int main() {

	population *pop = new population(pop_size, pop_deepth);
	
	for (int i=0; i<pop_size; i++) {
		cout <<"Eq." << setfill('0') << setw(3) << i << " resultado: ";
		cout << fixed << setprecision(5) << pop->pop[i]->recupera_valor();
		cout << "\texpressao: ";
		pop->pop[i]-> print_node();
		cout << endl ;
	}
	
  	delete pop;
		
	return 0;
}
