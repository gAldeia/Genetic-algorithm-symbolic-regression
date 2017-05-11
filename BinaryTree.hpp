#include <random>
#include <cstdlib>
#include <math.h>

#include <iostream>
#include <iomanip>

#include <queue>
#include <stack>

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
 *  	^ : expoente x^y
 */
const char   func_set[] = {'s', 'c', '*', '/', '+', '-','^'};
const char   term_set[] = {'x', '1'};

const int    func_set_size = 7;  //sizeof(func_set)/sizeof(func_set[0]);
const int    term_set_size = 2;  //sizeof(term_set)/sizeof(term_set[0]);



//---------------------------------------------------------------------------//
//                                                                           //
//                    Sessão de funções de utilidades                        //
//                                                                           //
//---------------------------------------------------------------------------//
 
char rand_func_set() {

	/** Função que retorna um elemento do conjunto de funções.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 *  	(Char) elemento aleatório do conjunto pré definido de funções.
	 */
	
	return func_set[ rand() % func_set_size ];
}

char rand_term_set() {

	/** Função que retorna um elemento do conjunto de terminais.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 *  	(Char) elemento aleatório do conjunto pré definido de terminais.
	 */
	 
	return term_set[ rand() % term_set_size ];
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

int aridade(char c) {

	/** Função que retorna a quantidade de números que a operação representada
	 *  pelo caractere passado precisa.
	 *  Parâmetros:
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Int) Aridade da função, podendo ser 1 ou 2.
	 * 		Caso o caractere não esteja no conjunto de funções, retorna 0.
	 */
	
	//neste caso, eu sei que as funções unárias estão até o elemento 1
	//do vetor, mas isso tem que ser ajustado para funcionar de forma
	//dinâmica.
	
	for (int i=0; i<func_set_size; i++) 
		if (c==func_set[i])
			return i<2 ? 1 : 2;
	return 0;
}

double numbera(char c, double x = 1.0) {
	
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
			cout << "erro numbera" << endl;
			return 0;
	}
}

double opera(double n, char c) {

	/** Função que retorna o resultado de uma operação unária.
	 *  Parâmetros:
	 * 		Double 'n', número a ser utilizado na operação;
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Double) Resultado da operação unária.
	 */
	
	n = n*PI;
	
	switch (c) {
		case 's':
			return sin(n/180.0);
		case 'c':
			return cos(n/180.0);
	}
}

double opera(double n, double m, char c) {

	/** Função que retorna o resultado de uma operação binária.
	 *  Parâmetros:
	 * 		Double 'n', número a ser utilizado na operação;
	 *		Double 'm', segundo número a ser utilizado na operação;
	 *  	Char 'c', contido no conjunto de funções.
	 *  Retorno:
	 *  	(Double) Resultado da operação binária.
	 */
	 
	switch(c) {
		case '*':
			return m*n;
		case '+':
			return m+n;
		case '/':
			return m!=0 ? n/m : 0;
		case '-':
			return n-m;
		case '^':
			return pow(n, m);
	}
}



//---------------------------------------------------------------------------//
//                                                                           //
//                 Sessão de declaração das classes principais               //
//                                                                           //
//---------------------------------------------------------------------------//

class node{
	
	/** Classe que compõe todos os nós de todas as árvores binárias.
	 *  Guarda as seguintes informações:
	 *  	value    : char que representa sua natureza (terminal ou operador);
	 * 		deepth   : int que representa sua profundidade máxima;
	 * 		esq, dir : ponteiros de nós, que apontam para seus possíveis filhos.
	 *  Possui os seguintes métodos:
	 *  	print_node     : Imprime recursivamente a equação da árvore.
	 *  	recupera_valor : retorna o resultado da operação da árvore.
	 * 		recupera_mse   : retorna o mse da árvore.
	 *		recupera_copia : retorna um ponteiro para uma cópia da árvore.
	 * 		mutation       : percorre a árvore, aplicando mutações sobre ela.
	 * 		crossover_with : recebe endereço de outra árvore, e efetua trocas
	 *					   : aleatórias de nós.
	 */
	 
	private:
		char value;
		int  deepth = 0;
		
		node *esq = NULL;
		node *dir = NULL;
		
	public:		
		node(int deepth);
		~node();
		
		void   print_node();
		double recupera_valor(double x);
		double recupera_mse(const double *target_values, const int n);
		node * recupera_copia();
		void   mutation(double mutation_rate);
		void   crossover_with(node *pai, double crossover_rate);
};

class population{

	/** classe que cria e gerencia um array de árvores binárias (população).
	 *  Guarda as seguintes informações:
	 * 		pop        : array de árvores principal;
	 * 		pop_backup : cópia de segurança do array de árvores principal;
	 * 		pop_size   : tamanho da população;
	 * 		pop_deepth : profundidade máxima que as árvores podem assumir;
	 * 	Possui os seguintes métodos:
	 * 		print_pop    : chama o método print_node em cada uma das árvores;
	 * 		print_backup : chama o print_node nas árvores do pop_backup; 
	 * 		fitness      : chama o mse em todas as árvores e retorna a árvore
	 * 					   que obteve o menor valor do mse;
	 * 		mutation     : chama o método mutation em cada uma das árvores;
	 *		set_backup   : copia o array pop no array pop_backup;
	 *		get_backup	 : copia o array backup no array pop;
	 *		next_gen	 : cria a próxima geração.
	 */
	
	private: 
		int pop_size;
		int pop_deepth;
	 
	public:
		node **pop;
		node **pop_backup;
		
		population(int pop_size, int pop_deepth);
		~population();
		
		void print_pop();
		void print_backup();
		node *fitness(const double *target_values, const int n);
		node *melhor_mse(double *target_values, int n);
		void mutation(double mutation_rate);
		void set_backup();
		void get_backup();
		void next_gen(double mutation_rate, double *target_values,
									int n, double crossover_rate);
};



//---------------------------------------------------------------------------//
//                                                                           //
//                  Sessão de implementação das funções                      //
//                                                                           //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//----------------------FUNÇÕES DA CLASSE NODE-------------------------------//
//---------------------------------------------------------------------------//

node::node(int deepth){
	
	/** Função construtora, que recebe a profundidade máxima e cria uma árvore
	 *  aleatóriamente. Caso a profundidade seja <0, o construtor não faz nada.
	 *  Parâmetros:
	 * 		int deepth, profundidade máxima.
	 *  Retorno:
	 * 		---
	 */	
	 
	this->deepth = deepth;
	
	//Se ainda não foi atigida a profundidade máxima, não preciso restringir a
	//criação de um nó. Se for atingida, necessariamente tenho que ter um 
	//terminal.
	if (deepth>1) {
		value = rand_everything();

		//se o nó for unário, precisará de um único filho, que por padrão fica
		//à direita.
		if (aridade(this->value)==1) {
			dir = new node(deepth-1);
		}
		//caso seja binário, precisará de 2.
		else if (aridade(this->value)==2){
			esq = new node(deepth-1);
			dir = new node(deepth-1);
		}
	}
	else if (deepth>0)
		value = rand_term_set();
}

node::~node(){

	delete esq;
	esq = NULL;
	
	delete dir;
	dir = NULL;
}

void node::print_node() {

	/** Função que imprime numa notação legível a equação que a árvore binária
	 *  representa. a impressão é feita de chamada recursiva, tendo como raiz
	 *  o nó que chamou a função.
	 *  Parâmetros:
	 * 		---
	 *  Retorno:
	 * 		---
	 */
	 
	if (value=='s') {
		cout << "sin("; dir->print_node(); cout << ")";	
	}
	else if (value=='c') {
		cout << "cos("; dir->print_node(); cout << ")";	
	}
	else if (aridade(value)==2) {
			cout << "("; esq->print_node();
			cout << value;
			dir->print_node(); cout << ")";	
	}
	else {
		cout << value;
	}
}

double node::recupera_valor(double x = 0.0) {
	
	/** Função que retorna o resultado da expressão da árvore que a chamou.
	 *  Parâmetros:
	 * 		double 'x', representando o valor que x assumirá, se necessário.
	 *  Retorno:
	 * 		(double) Resultado da f(x), onde f é a expressão da árvore e x o 
	 *      valor passado.
	 */
	 
	if (aridade(value)==0) {
		return numbera(value, x);
	}
	else {
		//verifico a aridade, para utilizar a função 'opera' corretamente.
		if (aridade(value)==1) {
			return opera( dir->recupera_valor(x), value );
		}
		else if (aridade(value)==2){
			return (opera( esq->recupera_valor(x),
						   dir->recupera_valor(x),
						   value) );
		}
	}
}

double node::recupera_mse(const double *target_values, const int n){
	
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
		mse += pow( ( recupera_valor(i)-target_values[i] ) ,2 );
	
	return sqrt(mse/double(n));
}

void node::mutation(double mutation_rate){

	/** Função que recebe o fator de mutação, e sorteia um número para ver se
	 *  o nó escolhido será modificado. Após isso, chama recursivamente a
	 *  mutação para seus filhos. Quando há mutação, ela verifica se a aridade
	 *  da operação continua a mesma, para evitar a criação de expressões invá-
	 *  lidas; caso a aridade tenha mudado, a árvore a partir daquele ponto é
	 *  reconstruída.
	 *  Parâmetros:
	 * 		double mutation_rate, variando de 0 a 100
	 *  Retorno:
	 * 		---
	 */
	
	int aridade_anterior = aridade(value);
	
	if (rand()%100<= mutation_rate) {
		
		if (deepth>1) {
			//eu preciso ter mais profundidade para colocar o terminal
			value = rand_everything();
		
			if ( aridade_anterior != aridade(value) ) {

				delete esq;
				esq = NULL;

				delete dir;
				dir = NULL;
			
				if (aridade(value)==1) 
					dir = new node(deepth-1);
					
				if (aridade(value)==2) {
					dir = new node(deepth-1);
					esq = new node(deepth-1);
				}
			}
		}
		else
			value = rand_term_set();
	}
	if (esq)
		esq->mutation(mutation_rate);
	if (dir)
		dir->mutation(mutation_rate);
}

node *node::recupera_copia() {

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
		aux->deepth = this->deepth;
		
		if (this->esq)
			aux->esq = this->esq->recupera_copia();
		if (this->dir)
			aux->dir = this->dir->recupera_copia();
	return aux;
}

void node::crossover_with(node *pai, double crossover_rate) {

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
			this->esq->crossover_with(pai->esq, crossover_rate);
		if (this->dir)
			this->dir->crossover_with(pai->dir, crossover_rate);
	}
}

//---------------------------------------------------------------------------//
//----------------------FUNÇÕES DA CLASSE POPULATION-------------------------//
//---------------------------------------------------------------------------//

population::population(int pop_size, int pop_deepth){

	/** Função construtora, que inicializa o array pop de acordo com o tamanho
	 *  passado, e cria n árvores aleatórias, todas com profundidade máxima
	 *  igual a pop_deepth.
	 * 	A função também já prepara o array pop_backup para ser utilizado caso
	 *  necessário.
	 *  Parâmetros:
	 * 		int pop_size, o tamanho da população;
	 * 		int pop_deepth, a profundidade máxima das árvores, passada para o
	 *						construtor dos nós.
	 *  Retorno:
	 * 		---
	 */

	this->pop_size = pop_size;	
	this->pop_deepth = pop_deepth;
	 
	pop = new node *[pop_size];
	pop_backup = new node *[pop_size];
	
	for (int i=0; i<pop_size; i++) {
		pop[i] = new node(pop_deepth);
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

void population::print_pop() {

	/** Função chama para cada árvore binária a função print_node(), no array
	 *  pop.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */
	 
	for (int i=0; i<pop_size; i++) {
		cout << "individuo " << i << ": ";
		pop[i]->print_node();
		cout << endl;
	}
}

node *population::fitness(const double *target_values, const int n){
	
	/** Função percorre a população, chamando para todas as árvores a função
	 *  recupera_mse; sempre armazenando a árvore que apresentou o menor mse.
	 *  Parâmetros:
	 *  	double[] target_values;
	 * 		int n, tamanho do target_values;
	 *  Retorno:
	 * 		(node) árvore com melhor mse.
	 */	

	double maior_mse = 0;

	for (int i=0; i<pop_size; i++) {
		if (pop[i]->recupera_mse(target_values, n) > maior_mse){
			maior_mse = pop[i]->recupera_mse(target_values, n);
		}
	}

	for (int i=0; i<pop_size; i++) {
		if (rand() % int(maior_mse)+1 > pop[i]->recupera_mse(target_values, n)){
			return pop[i];
		}
	}
	return pop[0];
}

node *population::melhor_mse(double *target_values, int n){

	int index = 0;
	double melhor = pop[index]->recupera_mse(target_values, n);

	for (int i=1; i<pop_size; i++){
		if (pop[i]->recupera_mse(target_values, n) < melhor){
			index = i;
			melhor = pop[index]->recupera_mse(target_values, n);
		}
	}
	return pop[index];
}


void population::mutation(double mutation_rate) {

	/** Função chama para cada árvore binária a função mutation().
	 *  Parâmetros:
	 *  	double mutation_rate, passado para a função mutation();
	 *  Retorno:
	 * 		---
	 */

	for (int i=0; i<pop_size; i++) {
		pop[i]->mutation(mutation_rate);
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
		pop_backup[i] = pop[i]->recupera_copia();	
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
		pop[i] = pop_backup[i]->recupera_copia();	
	}

}

void population::print_backup() {

	/** Função chama para cada árvore binária a função print_node(), porém no
	 *  array pop_backup.
	 *  Parâmetros:
	 *  	---
	 *  Retorno:
	 * 		---
	 */
	for (int i=0; i<pop_size; i++) {
		cout << "individuo " << i << ": ";
		pop_backup[i]->print_node();
		cout << endl;
	}
}

void population::next_gen(double mutation_rate, double *target_values, int n, double crossover_rate){
	
	/** A função recebe vários parâmetros, e faz: seleção, crossover, mutação e
	 *  a criação da nova população.
	 *
	 */

	node *aux1;
	node *aux2;

	set_backup();
	
	for (int i=0; i<=pop_size/2 ;i=i+2){
		aux1 = fitness(target_values, n)->recupera_copia();
		aux2 = fitness(target_values, n)->recupera_copia();

		aux1->crossover_with(aux2, crossover_rate);

		pop_backup[i] = aux1;
		pop_backup[i+1] = aux2;
	}

	get_backup();

	mutation(mutation_rate);
}
