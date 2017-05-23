#include <random>
#include <cstdlib>
#include <math.h>

//bibliotecas de entrada e saída de dados:
#include <iostream>
#include <iomanip>

#include <vector>

#define PI 3.141592;



using namespace std;

/** Array de funções: conjunto de caracteres que representam operações 
 *  unárias e binárias.
 *  Array de terminais: conjunto de caracteres que representam incognitas
 *  e constantes.
 *  Correspondencia dos caracteres:
 *  	* : Multiplicação x*y
 *  	/ : Divisão x/y
 *  	+ : Adição x+y
 *  	- : Subtração x-y
 *  	s : seno sen(x)
 *  	c : cosseno cos(x)
 * 		t : tangente tan(x)
 * 		l : logaritmo natural ln(x)
 * 		r : raiz quadrada sqrt(x)
 *  	^ : expoente x^y
 */

//conjuntos que definem o universo onde o algoritmo genético procurará a solução
vector<char> func_set = {'s', 'c', 't', 'l', 'r', '*', '/', '+', '-', '^'};
vector<char> term_set = {'x', '1'};



//---------------------------------------------------------------------------//
//-------------Sessão de implementação de métodos úteis----------------------//
//---------------------------------------------------------------------------//
 
char rand_func_set() {

	/** Função que retorna um elemento do conjunto de funções.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 *  	(Char) elemento aleatório do conjunto pré definido de funções.
	 */
	
	return func_set[ rand() % func_set.size() ];
}

char rand_term_set() {

	/** Função que retorna um elemento do conjunto de terminais.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 *  	(Char) elemento aleatório do conjunto pré definido de terminais.
	 */
	 
	return term_set[ rand() % term_set.size() ];
}

char rand_everything() {

	/** Função que retorna um elemento de qualquer um dos conjuntos.
	 *  A probabilidade de cada conjunto ser sorteado é igual.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 *  	(Char) aleatório, podendo ser tanto do conjunto de funções 
	 *  	quanto do conjunto de terminais.
	 */
	 
	if (rand() % 10 >= 5)
		return rand_func_set();
	else
		return rand_term_set();
}

int arity(char c) {

	/** Função que retorna a quantidade de números que a operação representada
	 *  pelo caractere passado precisa.
	 *  Parâmetros:
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Int) arity da função, podendo ser 1 ou 2.
	 * 		Caso o caractere não esteja no conjunto de funções, retorna 0.
	 */
	//{'s', 'c', 't', 'l', 'r', '*', '/', '+', '-', '^'}
	//neste caso, eu sei que as funções unárias estão até o elemento 1
	//do vetor, mas isso tem que ser ajustado para funcionar de forma
	//dinâmica.
	
	switch(c){
		case 's': return 1;
		case 'c': return 1;
		case 't': return 1;
		case 'l': return 1;
		case 'r': return 1;
		case '*': return 2;
		case '/': return 2;
		case '+': return 2;
		case '-': return 2;
		case '^': return 2;
		default : return 0;
	}
}

double numberfy(char c, double x = 1.0) {
	
	/** Função que recebe um caractere do conjunto de terminais e retorna
	 *  sua conversão para um valor numérico.
	 *  Parâmetros:
	 *  	Char 'c', c contido no conjunto de terminais;
	 *  	Double 'x', representando o valor que x pode assumir;
	 *  Retorno:
	 *  	(Double) Número equivalente ao caractere passado.
	 */
	 
	switch (c) {
		case 'x':
			return x;
		case '1':
			return 1;
		default:
			cout << "erro numberfy" << endl;
			return 0;
	}
}

double operate(double n, char c) {

	/** Função que retorna o resultado de uma operação unária.
	 *  Parâmetros:
	 * 		Double 'n', número a ser utilizado na operação;
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Double) Resultado da operação unária.
	 */

	switch (c) {
		case 's':
			n = n*PI;
			return sin(n/180.0);
		case 'c':
			n = n*PI;
			return cos(n/180.0);
		case 't':
			n = n*PI;
			return tan(n/180);
		case 'l':
			return log(n);
		case 'r':
			return sqrt(n);
	}
}

double operate(double n, double m, char c) {

	/** Função que retorna o resultado de uma operação binária.
	 *  Parâmetros:
	 * 		Double 'n', número a ser utilizado na operação;
	 *		Double 'm', segundo número a ser utilizado na operação;
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Double) Resultado da operação binária.
	 */
	 
	switch(c) {
		case '*': return m*n;
		case '+': return m+n;
		case '/': return m!=0 ? n/m : 0;
		case '-': return n-m;
		case '^': return pow(n, m);
	}
}



//--------------------------------------------------------------------------//
//--------------Sessão de declaração das classes principais-----------------//
//--------------------------------------------------------------------------//

class node{
	
	/** Classe que compõe todos os nós de todas as árvores binárias.
	 *  Guarda as seguintes informações:
	 *  	value    : char que representa sua natureza (terminal ou operador);
	 * 		depth   : int que representa sua profundidade máxima;
	 * 		esq, dir : ponteiros de nós, que apontam para seus possíveis filhos.
	 *  Possui os seguintes métodos:
	 *  	print_node_d     : Imprime recursivamente a equação da árvore.
	 *  	get_value : retorna o resultado da operação da árvore.
	 * 		get_mse   : retorna o mse da árvore.
	 *		get_copy : retorna um ponteiro para uma cópia da árvore.
	 * 		mutation       : percorre a árvore, aplicando mutações sobre ela.
	 * 		apply_crossover : recebe endereço de outra árvore, e efetua trocas
	 *					   : aleatórias de nós.
	 */
	 
	private:
		char value;
		int  depth = 0;
		
		node *esq = NULL;
		node *dir = NULL;
		
	public:		
		node(int depth);
		~node();
		
		void   print_node_d();

		double get_value(double x);
		double get_mse(const double *target_values, const int n);
		node * get_copy();

		void   apply_mutation(double mutation_rate);
		void   apply_crossover(node *pai, double crossover_rate);
};

class population{

	/** classe que cria e gerencia um array de árvores binárias (população).
	 *  Guarda as seguintes informações:
	 * 		pop        : array de árvores principal;
	 * 		pop_backup : cópia de segurança do array de árvores principal;
	 * 		pop_size   : tamanho da população;
	 * 		pop_depth : profundidade máxima que as árvores podem assumir;
	 * 	Possui os seguintes métodos:
	 * 		print_pop_d    : chama o método print_node_d em cada uma das árvores;
	 * 		print_backup_d : chama o print_node_d nas árvores do pop_backup; 
	 * 		fitness      : chama o mse em todas as árvores e retorna a árvore
	 * 					   que obteve o menor valor do mse;
	 * 		mutation     : chama o método mutation em cada uma das árvores;
	 *		set_backup   : copia o array pop no array pop_backup;
	 *		get_backup	 : copia o array backup no array pop;
	 *		generate_next_gen	 : cria a próxima geração.
	 */
	
	private: 
		int pop_size;
		int pop_depth;
	 
		node **pop;
		node **pop_backup;

	public:
		population(int pop_size, int pop_depth);
		~population();
		
		void print_pop_d();
		void print_backup_d();

		node *apply_fitness(const double *target_values, const int n);
		node *get_best_mse(double *target_values, int n);
		void apply_fitness_pop(double *target_values, int n);
		void apply_crossover_pop(double crossover_rate);
		void apply_mutation_pop(double mutation_rate);

		void set_backup();
		void get_backup();

		void generate_next_gen(double mutation_rate, double *target_values,
									int n, double crossover_rate);
};



//---------------------------------------------------------------------------//
//--------------Sessão de implementação dos métodos das classes--------------//
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//----------------------FUNÇÕES DA CLASSE NODE-------------------------------//
//---------------------------------------------------------------------------//

node::node(int depth){
	
	/** Função construtora, que recebe a profundidade máxima e cria uma árvore
	 *  aleatóriamente. Caso a profundidade seja <0, o construtor não faz nada.
	 *  Parâmetros:
	 * 		int depth, profundidade máxima.
	 *  Retorno:
	 * 		---
	 */	
	
	this->depth = depth;
	
	//Se ainda não foi atigida a profundidade máxima, não preciso restringir a
	//criação de um nó. Se for atingida, necessariamente tenho que ter um 
	//terminal.
	if (depth>1) {
		value = rand_everything();

		//se o nó for unário, precisará de um único filho, que por padrão fica
		//à direita.
		if (arity(this->value)==1) {
			dir = new node(depth-1);
		}
		//caso seja binário, precisará de 2.
		else if (arity(this->value)==2){
			esq = new node(depth-1);
			dir = new node(depth-1);
		}
	}
	else if (depth>0)
		value = rand_term_set();
}

node::~node(){

	if (esq){
		delete esq;
		esq = NULL;
	}
	if (dir){
		delete dir;
		dir = NULL;
	}
}

void node::print_node_d() {

	/** Função que imprime numa notação legível a equação que a árvore binária
	 *  representa. a impressão é feita de chamada recursiva, tendo como raiz
	 *  o nó que chamou a função.
	 *  Parâmetros:
	 * 		---
	 *  Retorno:
	 * 		---
	 */
	 
	if (value=='s') {
		cout << "sin("; dir->print_node_d(); cout << ")";	
	}
	else if (value=='c') {
		cout << "cos("; dir->print_node_d(); cout << ")";	
	}
	else if (value=='t'){
		cout <<"tan("; dir->print_node_d();cout<<")";
	}
	else if (value=='l'){
		cout <<"ln("; dir->print_node_d();cout<<")";
	}
	else if (value=='r'){
		cout <<"sqrt("; dir->print_node_d();cout<<")";
	}
	else if (arity(value)==2) {
			cout << "("; esq->print_node_d();
			cout << value;
			dir->print_node_d(); cout << ")";	
	}
	else {
		cout << value;
	}
}

double node::get_value(double x = 0.0) {
	
	/** Função que retorna o resultado da expressão da árvore que a chamou.
	 *  Parâmetros:
	 * 		double 'x', representando o valor que x assumirá, se necessário.
	 *  Retorno:
	 * 		(double) Resultado da f(x), onde f é a expressão da árvore e x o 
	 *      valor passado.
	 */
	 
	if (arity(value)==0) {
		return numberfy(value, x);
	}
	else {
		//verifico a arity, para utilizar a função 'operate' corretamente.
		if (arity(value)==1) {
			return operate( dir->get_value(x), value );
		}
		else if (arity(value)==2){
			return (operate( esq->get_value(x),
						   dir->get_value(x),
						   value) );
		}
	}
}

double node::get_mse(const double *target_values, const int n){
	
	/** Função que recebe um array contendo os valores alvo, e calcula o mse,
	 *  num intervalo entre 0 e n, sendo n o número de valores alvo.
	 *  Parâmetros:
	 * 		double[] target_values, contendo os valores alvo
	 * 		int n, sendo o tamanho do array target_values;
	 *  Retorno:
	 * 		(double) o mse calculado para a árvore.
	 */	
	
	double mse = 0;
	
	for (int i=0; i<n; i++)
		mse += pow( ( get_value(i)-target_values[i] ) ,2 );
	
	return sqrt(mse/double(n));
}

void node::apply_mutation(double mutation_rate){

	/** Função que recebe o fator de mutação, e sorteia um número para ver se
	 *  o nó escolhido será modificado. Após isso, chama recursivamente a
	 *  mutação para seus filhos. Quando há mutação, ela verifica se a arity
	 *  da operação continua a mesma, para evitar a criação de expressões invá-
	 *  lidas; caso a arity tenha mudado, a árvore a partir daquele ponto é
	 *  reconstruída.
	 *  Parâmetros:
	 * 		double mutation_rate, variando de 0 a 100
	 *  Retorno:
	 * 		---
	 */
	
	int arity_anterior = arity(value);
	
	if (rand()%100<= mutation_rate) {
		
		if (depth>1) {
			//eu preciso ter mais profundidade para colocar o terminal
			value = rand_everything();
		
			if ( arity_anterior != arity(value) ) {

				if (esq) {
					delete esq;
					esq = NULL;
				}
				if (dir) {
					delete dir;
					dir = NULL;
				}
				if (arity(value)==1) 
					dir = new node(depth-1);
					
				if (arity(value)==2) {
					dir = new node(depth-1);
					esq = new node(depth-1);
				}
			}
		}
		else
			value = rand_term_set();
	}
	if (esq)
		esq->apply_mutation(mutation_rate);
	if (dir)
		dir->apply_mutation(mutation_rate);
}

node *node::get_copy() {

	/** Função que retorna um ponteiro que aponta para uma cópia do nó que a
	 *  chamou. A cópia inclui o valor, profundidade e todos os filhos.
	 *  Parâmetros:
	 * 		---
	 *  Retorno:
	 * 		---
	 */

	node *aux;
	
		aux = new node(-1);
		
		aux->value = this->value;
		aux->depth = this->depth;
		
		if (this->esq)
			aux->esq = this->esq->get_copy();
		if (this->dir)
			aux->dir = this->dir->get_copy();
	return aux;
}

void node::apply_crossover(node *pai, double crossover_rate) {

	/** Função que recebe o ponteiro para o outro fornecedor de "DNA" e o fator
	 *  de troca de material. 
	 *  Parâmetros:
	 * 		ponteiro para um nó que trocará material com o nó que chamou 
	 *  	a função.
	 *  Retorno:
	 * 		---
	 */
	 
	node *auxdir;
	node *auxesq;
	char auxvalue;
	
	if (!pai)
		return;
		
	if (rand()%100<crossover_rate) {
		auxvalue = this->value;
		auxdir = this->dir;
		auxesq = this->esq;
		
		this->value = pai->value;
		this->esq = pai->esq;
		this->dir = pai->dir;
		
		pai->value = auxvalue;
		pai->esq = auxesq;
		pai->dir = auxdir;
	}
	else {
		if (this->esq)
			this->esq->apply_crossover(pai->esq, crossover_rate);
		if (this->dir)
			this->dir->apply_crossover(pai->dir, crossover_rate);
	}
}

//---------------------------------------------------------------------------//
//----------------------FUNÇÕES DA CLASSE POPULATION-------------------------//
//---------------------------------------------------------------------------//

population::population(int pop_size, int pop_depth){

	/** Função construtora, que inicializa o array pop de acordo com o tamanho
	 *  passado, e cria n árvores aleatórias, todas com profundidade máxima
	 *  igual a pop_depth.
	 * 	A função também já prepara o array pop_backup para ser utilizado caso
	 *  necessário.
	 *  Parâmetros:
	 * 		int pop_size, o tamanho da população;
	 * 		int pop_depth, a profundidade máxima das árvores, passada para o
	 *						construtor dos nós.
	 *  Retorno:
	 * 		---
	 */

	this->pop_size = pop_size;	
	this->pop_depth = pop_depth;
	 
	pop = new node *[pop_size];
	pop_backup = new node *[pop_size];
	
	for (int i=0; i<pop_size; i++) {
		pop[i] = new node(pop_depth);
		pop_backup[i] = new node (-1);
	}
}

population::~population(){

	for (int i=0; i<pop_size; i++) {
		delete pop[i];
		delete pop_backup[i];
	}
	delete pop;
	delete pop_backup;
}

void population::print_pop_d() {

	/** Função chama para cada árvore binária a função print_node_d(), no array
	 *  pop.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */
	 
	for (int i=0; i<pop_size; i++) {
		cout << "Subject " << i << ": ";
		pop[i]->print_node_d();
		cout << endl;
	}
}

node *population::apply_fitness(const double *target_values, const int n){
	
	/** Função percorre a população, chamando para todas as árvores a função
	 *  get_mse; sempre armazenando a árvore que apresentou o menor mse.
	 *  Parâmetros:
	 *  	double[] target_values;
	 * 		int n, tamanho do target_values;
	 *  Retorno:
	 * 		(node) árvore com melhor mse.
	 */	

	double highest_mse = 0;

	for (int i=0; i<pop_size; i++) {
		if (pop[i]->get_mse(target_values, n) > highest_mse){
			highest_mse = pop[i]->get_mse(target_values, n);
		}
	}

	for (int i=0; i<pop_size; i++) {
		if (rand() % (int(highest_mse) + 1) > pop[i]->get_mse(target_values, n)){
			return pop[i];
		}
	}
	return pop[rand() % pop_size];
}

node *population::get_best_mse(double *target_values, int n){

	int index = 0;
	double best = pop[index]->get_mse(target_values, n);

	for (int i=1; i<pop_size; i++){
		if (pop[i]->get_mse(target_values, n) < best){
			index = i;
			best = pop[index]->get_mse(target_values, n);
		}
	}
	return pop[index];
}

void population::apply_fitness_pop(double *target_values, int n){

	for (int i=0; i<pop_size; i++){
		delete pop_backup[i];
		pop_backup[i]= apply_fitness(target_values, n)->get_copy();
	}

}

void population::apply_crossover_pop(double crossover_rate){

	node *aux1;
	node *aux2;

	for (int i=0; i<pop_size -1 ;i=i+2){
		aux1 = pop[i]->get_copy();
		aux2 = pop[i+1]->get_copy();

		aux1->apply_crossover(aux2, crossover_rate);

		pop_backup[i] = aux1;
		pop_backup[i+1] = aux2;
	}

	get_backup();

}

void population::apply_mutation_pop(double mutation_rate) {

	/** Função chama para cada árvore binária a função mutation().
	 *  Parâmetros:
	 *  	double mutation_rate, passado para a função mutation();
	 *  Retorno:
	 * 		---
	 */

	for (int i=0; i<pop_size; i++) {
		pop[i]->apply_mutation(mutation_rate);
	}
}

void population::set_backup() {

	/** Função cria cópia de todo o array pop no array pop_backup.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */

	for (int i=0; i<pop_size; i++) {
		delete pop_backup[i];
		pop_backup[i] = pop[i]->get_copy();	
	}
}

void population::get_backup() {

	/** Função cria cópia de todo o array pop_backup no array pop.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */

	for (int i=0; i<pop_size; i++) {
		delete pop[i];
		pop[i] = pop_backup[i]->get_copy();	
	}

}

void population::print_backup_d() {

	/** Função chama para cada árvore binária a função print_node_d(), porém no
	 *  array pop_backup.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */
	for (int i=0; i<pop_size; i++) {
		cout << "Subject " << i << ": ";
		pop_backup[i]->print_node_d();
		cout << endl;
	}
}

void population::generate_next_gen(double mutation_rate, double *target_values, int n, double crossover_rate){
	
	/** A função recebe vários parâmetros, e faz: seleção, crossover, mutação e
	 *  a criação da nova população
	 */

	apply_fitness_pop(target_values, n);
	apply_crossover_pop(crossover_rate);
	apply_mutation_pop(mutation_rate);
}
