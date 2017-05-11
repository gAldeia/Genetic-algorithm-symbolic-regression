#include <iomanip>
#include <iostream>
#include <cstdio>

#include "BinaryTree.hpp"

using namespace std;



const int pop_size = 150;
const int pop_deepth = 5;

double mutation_rate = 20;
double crossover_rate = 50;

double target_values[] = {1.0, 4.0, 16.0, 64.0, 256.0};
int target_values_size = 5;



int main() {

	population *pop = new population(pop_size, pop_deepth);
	node *aux;
	double melhor;


	for (int i=0; i<1000; i++) {
		aux = pop->melhor_mse(target_values, target_values_size);

		melhor = aux->recupera_mse(target_values, target_values_size);

		if (melhor==0){
			cout << "ACHOU: "; aux->print_node();
			cout << "; na geração " << i << endl;
			break;
		}

		pop->next_gen(mutation_rate, target_values,
					  target_values_size, crossover_rate);
	}

	pop->melhor_mse(target_values, target_values_size)->print_node();
	cout << endl;
	pop->print_pop();

	delete pop;

	return 0;
}
