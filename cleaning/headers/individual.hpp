/// individual.hpp

#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

#include <vector>

#include "node.hpp"

using namespace std;

class Individual {

    private:
        double mse_value;

    public:
        Node *expression;   //a expressão é pública para facilitar os testes do código.

        Individual(bool grow = false, int maxDepth = 3, int numberOfXs = 1);
        ~Individual();

        //operações do ambiente
        Individual *crossover(double crossover_rate, Individual *parent);
        void        mutation(double mutation_rate);
        double      fitness(vector<utils::DataPoint> points);

        //conseguir ponteiro para cópia
        Individual *get_copy();

        //método de acesso a membros privados
        double      get_fitness();

        //método de debug
        void        print_expression_d();  //métodos de debug

};

#endif
