#include "BinaryTree.hpp"

using namespace std;



const int pop_size = 500;
const int pop_depth = 10;

double mutation_rate = 10;
double crossover_rate = 40;

double target_values[] = {1, 1, 2, 3, 5, 8, 13, 21, 34};
int target_values_size = 9;



int main() {

	srand(time(NULL));
	
	population *pop = new population(pop_size, pop_depth);
	node *aux;
	double melhor;


	for (int i=0; i<100; i++) {
		aux = pop->get_best_mse(target_values, target_values_size);

		melhor = aux->get_mse(target_values, target_values_size);

		if (melhor==0){
			cout << "ACHOU: "; aux->print_node_d();
			cout << "; na geração " << i << endl;
			break;
		}

		pop->generate_next_gen(mutation_rate, target_values,
					  target_values_size, crossover_rate);
	}

	pop->get_best_mse(target_values, target_values_size)->print_node_d();
	cout << endl;
	pop->print_pop_d();

	delete pop;

	return 0;
}
