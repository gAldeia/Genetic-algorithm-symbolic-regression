//----------------------------------------------------------------------------//
//Pequeno programa para estudar a herança de classes para prosseguir na imple-
//mentação do programa principal. A ideia aqui era reproduzir um algoritmo gené-
//tico de simples implementação encontrado no livro: Introduction to genetic
//algorithms, que encontra um inteiro que resolve a equação quadrática f(x).
//Porém, ao contrário do livro, o código aqui não foi implementado em C, e sim
//em C++ com os paradigmas de orientação a objetos, apenas para ter o primeiro
//contato com herança de classes, construtores, encapsulamento, etc.
//----------------------------------------------------------------------------//

#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>


using namespace std;


//função quadrática alvo, que será usada pelo programa para avaliar o fitness
//e buscar um inteiro x válido.
int f(int x){
    return x*x + 5*x + 6;
}


//----------------------------------------------------------------------------//
//---DECLARAÇÃO DAS CLASSES---------------------------------------------------//
//----------------------------------------------------------------------------//
class Genotype{ //classe base de tudo

    //Genótipo é a constituição genética de um ser vivo, refere-se ao gene
    //propriamente dito. A informação do genótipo é um vetor de 1s e 0s, que
    //é na verdade um numero em binário, porém neste problema ele é lido da
    //esquerda para a direita: 0000 -> 0, 1000 -> 1, 0110 -> 6.

    public:
        int cromo_size;
        int *cromosome;

        Genotype(int cromo_size, int *cromo);
        ~Genotype();
        string get_genotype_d();
};

class Phenotype : public Genotype{ //O fenótipo herda o genótipo, uma vez que 
                                   //depende dele para existir.

    //Fenótipo é o resultado da expressão do fenótipo. Então, neste problema, o
    //genótipo é a informação codificada, escrita em 0s e 1s num vetor, enquanto
    //o fenótipo é a expressão dessa informação (decodificada em decimal, uma
    //"linguagem" que nós entendemos).

    private:
        int decimal_value;
        int fitness;

    public:
        Phenotype(int cromo_size, int *cromo);

        int get_decimal_value();
        int get_fitness();
    
        void evaluate_decimal();
        void evaluate_fitness();
};

class Gene : public Phenotype { //o gene herda o fenótipo e o genótipo.

    //é aqui que as operações sobre a informação codificada acontecem: os méto-
    //dos dessa classe que operam sobre a informação.

    public:
        Gene(int cromo_size, int *cromo);

        Gene *clone();
        void mutate(int mutation_rate);
        void crossover_with(Gene *parent);
};

class Gene_pool{

    //Classe equivalente ao "pool gênico", que contém todos os genes da popu-
    //lação. Esta classe que realiza os eventos "globais" sob a população:
    //a seleção por aptidão, a reprodução dos individuos, o crossover e a muta-
    //ção.

    private:
        int pop_size;
        int cromo_size;
    public:
        Gene **pop;

        Gene_pool(int pop_size, int cromo_size);

        void tournament_selection();
        void crossover_and_mutation(int mutation_rate);
        void print_pop_d();
        bool check_and_print();
};


//----------------------------------------------------------------------------//
//---IMPLEMENTAÇÃO DA CLASSE GENÓTIPO-----------------------------------------//
//----------------------------------------------------------------------------//
Genotype::Genotype(int cromo_size, int *cromo){

    //construtor do genótipo: se for passado como parametro um array de inteiros
    //ele assume que isso seja um outro genótipo e que deve apenas copiar sua
    //informação. Caso o ponteiro do array seja NULL, ele cria um novo genótipo
    //aleatóriamente.

    this->cromo_size = cromo_size;

    cromosome = new int[cromo_size];
    if (!cromo) {
        for (int i=0; i<cromo_size; i++)
            cromosome[i] = rand()%2;
    }
    else {
        for (int i=0; i<cromo_size; i++)
            cromosome[i] = cromo[i];
    }
}

Genotype::~Genotype(){
    delete[] cromosome;
}

string Genotype::get_genotype_d(){

    //retorna uma string contendo a informação do genótipo, útil para
    //imprimir na tela a informação contida na classe.

    string str = "";
    char aux;
    for(int i=0; i<cromo_size; i++){
        aux = cromosome[i]==1?'1':'0';
        str = str + aux;
    }
    return str;
}


//----------------------------------------------------------------------------//
//---IMPLEMENTAÇÃO DA CLASSE FENÓTIPO-----------------------------------------//
//----------------------------------------------------------------------------//
Phenotype::Phenotype(int cromo_size, int *cromo) : Genotype(cromo_size, cromo){

    //um construtor, quando herda uma outra classe, chama primeiro o construtor
    //da classe herdada para depois executar seu próprio construtor. Então,
    //primeiro ele cria o genótipo e imediatamente já atualiza os valores do
    //fenótipo.

    evaluate_decimal();
    evaluate_fitness();
};

void Phenotype::evaluate_decimal(){

    //atualiza o valor decimal do gene. A informação está sendo codificada
    //como um binário de complemento para 2, porém lido da esquerda para a
    //direita por questões de facilidade de implementação. Esta função
    //transforma esse binário em decimal.

    decimal_value = 0;

    for (int i=0; i<cromo_size-1; i++)
        decimal_value +=cromosome[i] * pow(2, i);

    decimal_value = decimal_value - cromosome[cromo_size-1]*pow(2,cromo_size-1);
}

void Phenotype::evaluate_fitness(){

    //usa o valor decimal do gene na função alvo f(x). Um fitness=0 significa
    //que o decimal é uma raiz da equação.

    fitness = f(decimal_value); //equação alvo aqui
}

int Phenotype::get_decimal_value(){
    return decimal_value;
}

int Phenotype::get_fitness(){
    return fitness;
}


//----------------------------------------------------------------------------//
//---IMPLEMENTAÇÃO DA CLASSE GENE---------------------------------------------//
//----------------------------------------------------------------------------//
Gene::Gene(int cromo_size, int *cromo=NULL) : Phenotype(cromo_size, cromo){

    //este construtor não faz nada, mas precisa ser ao menos declarado
    //para passar à classe herdada as informações necessárias para seu constru-
    //tor. Como esta é a classe mais alta (gene>fenótipo>genótipo), ela recebe
    //tudo que é necessário para construir suas heranças.
    //Caso nenhum valor seja passado para o int *cromo, ele recebe NULL.
}

Gene *Gene::clone(){
    
    //retorna um ponteiro para uma cópia desta classe gene

    Gene *aux = new Gene(cromo_size, cromosome);
    return aux;
}

void Gene::mutate(int mutation_rate){

    //percorre o vetor codificado, com uma chance de ocorrer uma mutação na
    //informação contida. sempre após a mutação o valor decimal é atualizado.

    for (int j=0; j<cromo_size; j++){
        if (rand()%100<= mutation_rate){
            cromosome[j] = rand()%2;
        }
    }
    evaluate_decimal();
    evaluate_fitness();
}

void Gene::crossover_with(Gene *parent){

    //recebe um ponteiro para outro gene, realiza um corte aleatório no meio da
    //informação codificada e troca as duas partes entre eles.
    
    int cut;
    int aux;

    cut = rand()%cromo_size;

    for (int j=0; j<cut; j++){
        aux = this->cromosome[j];
        this->cromosome[j] = parent->cromosome[j];
        parent->cromosome[j] = aux;
    }

    evaluate_decimal();
    evaluate_fitness();
}


//----------------------------------------------------------------------------//
//---IMPLEMENTAÇÃO DA CLASSE GENE_POOL----------------------------------------//
//----------------------------------------------------------------------------//
Gene_pool::Gene_pool(int pop_size, int cromo_size){

    //inicializa a população de genes.

    this->pop_size = pop_size;
    this->cromo_size = cromo_size;

    pop = new Gene *[pop_size];
    
    for(int i=0; i<pop_size; i++){
        pop[i] = new Gene(cromo_size);
    }
}


void Gene_pool::tournament_selection(){

    //seleção por torneio, que pega aleatóriamente 2 indivíduos e avalia seus
    //respectivos fitness, e o mais "apto" é jogado para a próxima geração

    int i=0;

    Gene **new_pop = new Gene *[pop_size];

    while(i<pop_size){

        int s1 = rand()%pop_size;
        int s2 = rand()%pop_size;

        if (pop[s1]->get_fitness() < pop[s2]->get_fitness()){
            new_pop[i] = new Gene(cromo_size, pop[s1]->cromosome);
        }
        else{
            new_pop[i] = new Gene(cromo_size, pop[s2]->cromosome); 
        }
        i++;
    }
    for (i=0; i<pop_size; i++){
        pop[i] = new_pop[i]->clone();
        delete new_pop[i];
    }
    delete new_pop;
}

void Gene_pool::print_pop_d(){

    //imprime na tela informações sobre a geração atual

    cout << "Genotype\tPhenotype\tFitness" << endl;
    for (int i=0; i<pop_size; i++){
        cout << pop[i]->get_genotype_d();
        cout << "\t\t" << pop[i]->get_decimal_value();
        cout << "\t\t\t" << pop[i]->get_fitness() << endl;
    }
}

void Gene_pool::crossover_and_mutation(int mutation_rate){

    //faz na população as operações de crossover e mutação. Deve ser chamada
    //depois de realizar uma seleção (no caso seleção de torneio), pois precisa
    //operar com os indivíduos já selecionados

    for(int i=0; i<pop_size/2;i++){
        pop[i]->crossover_with(pop[2*i]);
        pop[i]->mutate(mutation_rate);
        pop[2*i]->mutate(mutation_rate);
    }
}

bool Gene_pool::check_and_print(){

    //verifica se o genótipo perfeito já foi encontrado, e caso sim, retorna
    //verdadeiro e para o programa.

    for(int i=0; i<pop_size; i++){
        if (pop[i]->get_fitness()==0){
            cout << "ACHOU: " << pop[i]->get_decimal_value() << endl;
            return true;
        }
    }
    return false;
}
