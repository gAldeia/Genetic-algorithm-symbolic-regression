#include <iomanip>
#include <iostream>
#include <cstdio>

#include "BinaryTree.hpp"

using namespace std;

const int pop_size = 25;
const int pop_deepth = 4;

const double mutation_rate = 20;

const double target_values[] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
const int    target_values_size = 7;

int main() {

	population *pop = new population(pop_size, pop_deepth);

	cout << "pop:" << endl;
	pop->print_pop();
	cout << endl;

	pop->set_backup();
	pop->mutation(mutation_rate);
	
	cout << "backup: " << endl;
	pop->print_backup();
	cout << endl;
	
	cout << "pop apos mutating: " << endl;
	pop->print_pop();
	cout << endl;

	for (int i=0; i<pop_size; i++)
		cout <<"MSE " << i << ": " << pop->pop[i]->recupera_mse(target_values, target_values_size) << endl;
		
	cout << endl;
	
	node aux = pop->fitness(target_values, target_values_size);
	
	cout << "melhor eq selecionada pelo fitness: ";
	aux.print_node();
	cout << endl << endl;
	
	node *copia1, *copia2;
	
	for (int i=0; i< pop_size-1; i++) {
		cout << "pais: " << endl;
		copia1 = pop->pop[i]->recupera_copia();
		copia2 = pop->pop[i+1]->recupera_copia();
		cout << "\t"; copia1->print_node(); cout << endl;
		cout << "\t"; copia2->print_node(); cout << endl;
	
		cout << "filhos: " << endl;
		copia1->crossover_with(copia2, 25);
		cout << "\t"; copia1->print_node(); cout << endl;
		cout << "\t"; copia2->print_node(); cout << endl << endl;
	}
	
  	delete pop;
		
	return 0;
}
