//obs: o random que estou usando é da bibio stdlib, preciso adaptar para usar
//o da biblio random do C++

#include <random>
#include <cstdlib>
#include <math.h>

#include <iostream>

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

const char func_set[] = {'*', '/', '+', '-', 's', 'c', '^'};
const char term_set[] = {'x', 'y', 'z', '3'};
 
const int func_set_size = 7; //sizeof(func_set)/sizeof(func_set[0])
const int term_set_size = 4; //sizeof(term_set)/sizeof(term_set[0])

double globalX=1.0;
double globalY=1.0;
double globalZ=1.0;



char rand_func_set(){
	/** A função não recebe nada como parametro, e retorna um caractere
	 *  escolhido "aleatoriamente" do conjunto de funções, que representa
	 *  alguma operação (descrita no início do código).
	 */
	 
	return func_set[ rand() % func_set_size ];
}

char rand_term_set(){
	/** A função não recebe parametro, e retorna um caractere "aleatório" do
	 *  conjunto de terminais, podendo ser uma constante ou uma variável. A
	 *  função é ideal para criar/completar as folhas das árvores geradas.
	 */

	return term_set[ rand() % term_set_size ];
}

char rand_everything() {
	/** A função não recebe parametro, e tem 50% de chance de retornar um 
	 *  caractere pertencente ao conjunto de funções e 50% de retornar um 
	 *  caractere pertencente ao conjunto de terminais. Ideal para a criação
	 *  de nós que não precisam ter um tipo específico (função ou terminal)
	 */
	 
	if (rand() % 2 ==0)
		return rand_func_set();
	else
		return rand_term_set();
}

int is_func(char c) {
	/** Recebe como parametro um caractere e verifica se ele pertence ao con-
	 *  junto de funções. Caso não pertenca, retorna 0. Caso pertenca, retorna
	 *  a aridade da função (1 para funções unárias e 2 para funções binárias).
	 *  OBS: é importante lembrar que zero é considerado como falso, então
	 *  esta função pode ser usada também para ver se é verdadeiro ou não.
	 */
	 
	switch (c){
		case '+':
			return 2;
		case '-':
			return 2;
		case '*':
			return 2;
		case '/':
			return 2;
		case '^':
			return 2;
		case 's':
			return 1;
		case 'c':
			return 1;
	}

	return 0;
}

bool is_term(char c) {
	/** Recebe como parametro um caractere e verifica se ele pertence ao con-
	 *  junto de terminais.
	 */
	 
	 for (int i=0; i<term_set_size; i++)
	 	if (c==term_set[i])
	 		return true;
	 
	 return false;
}

double number(char c){
	/** Função recebe um caractere que representa um número e retorna o seu
	 *  equivalente numérico.
	 */
	 
	switch (c) {
		case 'x':
			return globalX;
		case 'y':
			return globalY;
		case 'z':
			return globalZ;
		case '3':
			return 3;
		default:
			return 0;
	}
}

double opera (double n, char c) {

	n = n*PI;
	switch (c) {
		case 's':
			return sin(n/180.0);
		case 'c':
			return cos(n/180.0);
		default:
			cout << "erro no opera (unario)" << endl;
			return -1;
	}
}

double opera (double n, double m, char c) {
	switch(c) {
		case '*':
			return m*n;
		case '+':
			return m+n;
		case '/':
			return n/m;
		case '-':
			return n-m;
		case '^':
			return pow(n, m);
	}
}



class node{
	/** Classe que representa o nó das árvores. Um nó tem as seguintes proprie-
	 *  dades: valor, filho esquerdo (esq) e filho direito (dir).
	 */ 
	
	public:
		char value;
		
		node *esq = NULL;
		node *dir = NULL;
		
		node();
		~node();
		
		void print_node();
		double recupera_valor();
};

node::node(){
	/** O construtor sempre cria um nó com um valor aleatório. Caso seja
	 *  necessário especificar algum tipo (função ou terminal) para o nó,
	 *  deve-se modificá-lo posteriormente. Os métodos relacionados aos nós
	 *  (tais como crossover e mutação) pertencem à esta classe, e os métodos
	 *  relacionados com a população geral pertencem à classe população.
	 *  Se o nó criado for uma função binária, seus dois filhos serão gerados.
	 *  Se for uma função unária, seu único flho será gerado (no nó esquerdo).
	 */

	this->value = rand_everything();
	
	if (is_func(this->value)==1){
		this->esq = new node();
	}
	else if (is_func(this->value)==2){
		this->esq = new node();
		this->dir = new node();
	}
}

node::~node(){
	/** O destrutor DEVERÁ desalocar a memória de todos os filhos, já que
	 *  será chamado quando a raiz for destruida.
	 */
}

void node::print_node() {
	/** Função que imprime o nó que a chamou. a impressão é feita da seguinte
	 *  forma: primeiro, é conferido se o nó tem um filho à esquerda - se exis-
	 *  tir, ele chama recursivamente a função à esquerda. Depois, ele chama
	 *  recursivamente para a direita. Por fim, ele imprime seu valor.
	 *  Isso faz com que a impressão seja feita na notação pós-fixa (RPN).
	 */
	 
	if (this->esq!=NULL)
		this->esq->print_node();
			
	if (this->dir!=NULL)
		this->dir->print_node();

	cout << this->value;
}

double node::recupera_valor() {
	/** Função que ao ser chamada retorna o resultado da expressão da arvore.
	 *  Quando um nó não tem os dois resultados prontos, ela é passada
	 *  recursivamente para os filhos que ainda não resolveram as operações
	 *  para então poder calcular o valor do nó.
	 */
	 
	if (is_term(this->value)) {
		return number(this->value);
	}
	else {
		if (is_func(this->value)==1) {
			return opera(this->esq->recupera_valor(), this->value );
		}
		else if (is_func(this->value)==2){
			return (opera( this->esq->recupera_valor(), this->dir->recupera_valor(), this->value) );
		}
		else {
			cout << "erro no recupera_valor" << endl;
		}
	}
}



class population{
	/** Essa é a classe população. Tem como atributos apenas um array de nós
	 *  e um inteiro para armazenar o tamanho da população. Todas os métodos
	 *  que funcionam sobre a população deverão pertencer a ela (como fitness
	 *  e chamada da próxima geração, por exemplo). Os métodos que ocorrem no
	 *  "DNA" pertencem à classe node (tais como crossover e mutação).
	 */

	public:
		node **pop;
		
		int pop_size;
		
		population(int pop_size);
		~population();
		
		void print_pop();
};

population::population(int pop_size){

	/** o construtor define o tamanho da população e cria um array do 
	 *  tamanho da população, iniciando em cada um dos elementos um 
	 *  novo nó, que será a raiz de cada indivíduo. É importante lembrar que
	 *  a criação de um nó sempre gera um valor aleatório de qualquer um dos
	 *  conjuntos (terminal e função).
	 */

	this->pop_size = pop_size;	 
	this->pop = new node*[pop_size];
	
	for (int i=0; i<pop_size; i++)
		this->pop[i] = new node();
}

population::~population(){
	/** O destrutor deleta todas as raízes, enquanto o destrutor da raiz
	 *  deleta todos os seus respectivos filhos. Após isso, ele deleta o
	 *  ponteiro do array e morre.
	 */

	for (int i=0; i<this->pop_size; i++)
		delete this->pop[i];
	
	delete this->pop;
}

void population::print_pop() {
	/** Para imprimir a população, é precisso imprimir individuo por individuo, 
	 *  então o método apenas imprime o número do individuo e chama a função
	 *  print_node().
	 */

	for (int i=0; i<this->pop_size; i++) {
		cout << "individuo " << i << ": ";
		pop[i]->print_node();
		cout << endl;
	}
}




















