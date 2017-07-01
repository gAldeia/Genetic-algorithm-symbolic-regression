//----------------------------------------------------------------------------//
//Pequeno programa para estudar a herança de classes para prosseguir na imple-
//mentação do programa principal. A ideia aqui era reproduzir um algoritmo gené-
//tico de simples implementação encontrado no livro: Introduction to genetic
//algorithms, que encontra um inteiro que resolve a equação quadrática f(x).
//Porém, ao contrário do livro, o código aqui não foi implementado em C, e sim
//em C++ com os paradigmas de orientação a objetos, apenas para ter o primeiro
//contato com herança de classes, construtores, encapsulamento, etc.
//----------------------------------------------------------------------------//


#include "quadratic-solver-reference-header.hpp"


using namespace std;


const int pop_size = 10;        //tamanho da população
const int cromo_size = 6;       //tamanho do vetor codificado
const int mutation_rate = 20;   //0% a 100%


int main(){

    //seed do rand()
    srand(time(NULL));

    //contador de gerações
    int gen = -1;

    //crio uma classe population
    Gene_pool *population = new Gene_pool(pop_size, cromo_size);

    //evolução da população
    while (true){

        //imprimo informações da geração na tela
        cout << "\nGeração " << ++gen << endl;
        population->print_pop_d();

        //verifico se o indivíduo perfeito já foi encontrado, caso sim,
        //paro o laço e imprimo seu fenótipo.
        if (population->check_and_print())
            break;

        //evoluo a população para a próxima geração
        population->tournament_selection();
        population->crossover_and_mutation(mutation_rate);
    }

    return 0;
}
