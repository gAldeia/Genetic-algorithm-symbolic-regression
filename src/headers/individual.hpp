//individual.hpp
#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

#include <vector>

#include "node.hpp"


using namespace std;


class Individual{
    
    private:
        double mse_value;

    public:
        Node *expression;

        Individual(bool grow = false, int maxDepth = 3, int numberOfXs = 1);
        ~Individual();

        Node *crossover(double crossover_rate, Individual parent);
        void mutation(double mutation_rate);
        double fitness(vector<utils::DataPoint> points);

        void print_expression_d();
        void print_fitness_d();
};

#endif