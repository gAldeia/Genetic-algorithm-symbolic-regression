//individual.hpp
#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

#include <vector>

#include "node.hpp"


using namespace std;


class Individual{
    
    private:
        Node *expression;
        double mse_value;

    public:
        Individual(int numberOfXs);
        ~Individual();

        Node *crossover(double crossover_rate, Individual parent);
        void mutation(double mutation_rate);
        double fitness(vector<utils::DataPoint> points);
        void print_expression_d();
};

#endif
