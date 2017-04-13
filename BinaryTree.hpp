#include <random>
#include <queue>
#include <stack>

using namespace std;

// * : Multiplicação
// / : Divisão
// + : Adição
// - : Subtração
// s : sen(x)
// c : cos(x)
const int func_set_size = 6;
const int term_set_size = 3;
const char func_set[] = {'*', '/', '+', '-', 's', 'c'};
const char term_set[] = {'x', 'y', 'z'};






char random_function_set(){
	//retorna um elemento aleatório do comjunto de funções
	char ret = func_set[ rand() % func_set_size ];
	
	return ret;
}

char random_terminal_set(){
	//retorna um elemento aleatório do conjunto de números
	char ret = term_set[ rand() % term_set_size ];
	
	return ret;
}

char random_everything() {
	//pode retornar qualquer elemento de qualquer um dos conjuntos
	if (rand() % 2 ==0)
		return random_function_set();
	else
		return random_terminal_set();
}

bool is_this_function(char c) {
	//verifica se o nó da árvore é uma função. Uma função de aridade 1
	//recebe só 1 numero (ex: seno, cosseno, e^x), e uma função de aridade
	//2 recebe 2 (ex: 1*1, 2+2)
	for (int i=0; i<func_set_size; i++){
		if (c==func_set[i]){
			return true;
		}
	}
	return false;
}






class node{
	public:
		char value;
		
		node *esq = NULL;
		node *dir = NULL;
		
		node();
		~node();
		
		void imprime_node();
};

node::node(){
	//o construtor sempre gera um valor aleatório para o nó,
	//sendo necessário modificá-lo quando necessário. Ele não irá gerar filho
	//para constantes. O tamanho da árvore não é definido, pois os filhos serão
	//gerados aleatóriamente.
	this->value = random_everything();
	if (is_this_function(this->value)){
		if ( (rand() % 10) > 1 ){
			this->esq = new node();
		}
		if ( (rand() % 10) > 1 ) {
			this->dir = new node();	
		}
	}
}

node::~node(){

}

void node::imprime_node() {

	//imprime os valores da árvore binária com notação 
	//pós fixa (RPN) recursivamente
	if (this->esq!=NULL){
		this->esq->imprime_node();
	}	
	if (this->dir!=NULL){
		this->dir->imprime_node();
	}
	cout << this->value;
}





class population{
	public:
		node **pop;
		
		int pop_size;
		
		population(int pop_size);
		~population();
		
		void imprime_pop();
};

population::population(int pop_size){

	//o construtor cria um array do tamanho da população, e inicia em cada
	//um dos índices um novo nó, que será a raiz de cada indivíduo.
	this->pop = new node*[pop_size];
	this->pop_size = pop_size;
	
	for (int i=0; i<pop_size; i++) {
		this->pop[i] = new node();
	}
}

population::~population(){
	for (int i=0; i<this->pop_size; i++) {
		delete this->pop[i];
	}
	delete this->pop;
}

void population::imprime_pop() {
	for (int i=0; i<this->pop_size; i++) {
		cout << "individuo " << i << ": ";
		pop[i]->imprime_node();
		cout << endl;
	}
}





















