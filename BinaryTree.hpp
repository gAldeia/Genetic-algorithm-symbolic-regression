#include <random>
#include <cstdlib>
#include <math.h>

#include <iostream>
#include <iomanip>

#include <queue>
#include <stack>

#define PI 3.141592;

using namespace std;

/** O conjunto de funções é composto por operações unárias e binárias, e pre-
 *  cisam sempre de pelo menos um numero real para retornarem um valor.
 *  O conjunto de terminais são os valores de entrada e constantes, utilizadas
 *  nas funções para retornar valores.
 *  Correspondencia dos caracteres:
 *  	- * : Multiplicação x*y
 *  	- / : Divisão x/y
 *  	- + : Adição x+y
 *  	- - : Subtração x-y
 *  	- s : seno sen(x)
 *  	- c : cosseno cos(x)
 *  	- ^ : expoente x^y
 */

//as funções unárias ficam no começo do vetor, para facilitar reconhecimento
const char   func_set[] = {'s', 'c', '*', '/', '+', '-','^'};
const char   term_set[] = {'x', 'y', '3'};
const double term_values[] = {-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0};

const int    func_set_size = 7;    //sizeof(func_set)/sizeof(func_set[0]);
const int    term_set_size = 3;    //sizeof(term_set)/sizeof(term_set[0]);
const int    term_values_size = 7; //sizeof(term_values)/sizeof(term_values[0]);



char rand_func_set(){
	 
	//retorna um elemento aleatório do conjunto de funções 
	
	return func_set[ rand() % func_set_size ];
}

char rand_term_set(){
	
	//retorna um elemento aleatório do conjunto de terminais

	return term_set[ rand() % term_set_size ];
}

char rand_everything() {
	
	//retorna um elemento aleatório de qualquer um dos conjuntos, com uma chance
	//de 50% de retornar do conjunto de terminal e 50% do conjunto de funções.
	 
	if (rand() % 2 ==0)
		return rand_func_set();
	else
		return rand_term_set();
}

int is_func(char c) {
	
	//retorna a aridade da função que o caractere passado representa. se o
	//caractere for um número, retorna zero.
	
	//os operadores unarios vao ate o indice 1 do vetor.
	for (int i=0; i<func_set_size; i++) 
		if (c==func_set[i])
			return i<2 ? 1 : 2;

	return 0;
}

double numbera(char c, double x = 1.0, double y = 1.0){
	
	//retorna o valor numerico que um caractere representa. para variaveis,
	//deve ser passado o valor elas podem assumir (ou, caso contrário, será
	//atribuido 1 para elas).
	 
	switch (c) {
		case 'x':
			return x;
		case 'y':
			return y;
		case '3':
			return 3;
		default:
			return 0;
	}
}

double opera (double n, char c) {

	//função que resolve operações unárias. deve ser passado um numero e 
	//a função unária

	n = n*PI;
	
	switch (c) {
		case 's':
			return sin(n/180.0);
		case 'c':
			return cos(n/180.0);
	}
}

double opera (double n, double m, char c) {

	//função que resolve operações binárias.

	switch(c) {
		case '*':
			return m*n;
		case '+':
			return m+n;
		case '/':
			return m!=0 ? n/m : 1;
		case '-':
			return n-m;
		case '^':
			return pow(n, m);
	}
}



class node{
	
	private:
		//as variaveis dos nós são private para
		//evitar acessos de outros métodos.
		
		char value;
		
		node *esq = NULL;
		node *dir = NULL;
	
	public:		
		node(int deepth);
		~node();
		
		void print_node();
		double recupera_valor(double x, double y);
};

node::node(int deepth){
	
	//o construtor recebe a profundidade máxima que seus filhos podem ter
	//e cria uma árvore aleatoriamente.
	
	//verifico se já atingi a profundidade máxima da árvore. caso não,
	//a criação de um novo nó não precisa ser restringida.
	if (deepth>1) {
		this->value = rand_everything();

		//se o nó for unário, precisará de um único valor
		if (is_func(this->value)==1)
			this->dir = new node(deepth-1); 
	
		//caso seja binário, precisará de 2.
		else if (is_func(this->value)==2){
			this->esq = new node(deepth-1);
			this->dir = new node(deepth-1);
		}
	}
	else
		this->value = rand_term_set();
}

node::~node(){

	delete this->esq;
	this->esq = NULL;

	delete this->dir;
	this->dir = NULL;
}

void node::print_node() {

	//imprime na notação usual a expressão da árvore.

	if (this->value=='s') {
		cout << "sin("; this->dir->print_node(); cout << ")";	
	}
	else if (this->value=='c') {
		cout << "cos("; this->dir->print_node(); cout << ")";	
	}
	else if (is_func(this->value)==2) {
			cout << "("; this->esq->print_node();
			cout << this->value;
			this->dir->print_node(); cout << ")";	
	}
	else {
		cout << this->value;
	}
}

double node::recupera_valor(double x = 1.0, double y = 1.0) {
	
	//Função que ao ser chamada retorna o resultado da expressão da arvore que
	//a chamou.
	 
	if (is_func(this->value)==0) {
		return numbera(this->value, x, y);
	}
	else {
		//a função opera é sobrecarregada para calcular dependendo da aridade
		if (is_func(this->value)==1) {
			return opera(this->dir->recupera_valor(), this->value );
		}
		else if (is_func(this->value)==2){
			return (opera( this->esq->recupera_valor(),
						   this->dir->recupera_valor(),
						   this->value) );
		}
	}
}



class population{

	public:
		node **pop;
		
		int pop_size;
		
		population(int pop_size, int pop_deepth);
		~population();
		
		void print_pop();
};

population::population(int pop_size, int pop_deepth){

	//o construtor cria a população com o tamanho de individuos e a profundi-
	//dade máxima passada.

	this->pop_size = pop_size;	 
	this->pop = new node*[pop_size];
	
	for (int i=0; i<pop_size; i++)
		this->pop[i] = new node(pop_deepth);
}

population::~population(){

	for (int i=0; i<this->pop_size; i++)
		delete this->pop[i];
	delete this->pop;
}

void population::print_pop() {

	//imprime, em cada linha, a equação de cada um dos individuos.
	for (int i=0; i<this->pop_size; i++) {
		cout << "individuo " << i << ": ";
		pop[i]->print_node();
		cout << endl;
	}
}
