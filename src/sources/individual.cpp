//individual.cpp
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/individual.hpp"
#include "../headers/utils.hpp"


Individual::Individual(bool grow, int maxDepth, int numberOfXs){
    expression = new Node(grow, maxDepth, numberOfXs);
}

Individual::~Individual(){
    delete expression;
}

Node *Individual::crossover(double crossover_rate, Individual parent){
    //falta implementar aqui
}

void Individual::mutation(double mutation_rate){
    //falta implementar aqui
}

double Individual::fitness(std::vector<utils::DataPoint> points){
   
    double mse = 0.0;
    
    for(int i=0; i<points.size(); i++)
        mse += utils::uPow((expression->eval(points[i])-points[i].y ), 2);
    
    this->mse_value = utils::uSqrt(mse/(double)points.size());
    
    return this->mse_value;
}

void Individual::print_expression_d(){
    expression->print_node_d();
}

void Individual::print_fitness_d(){
    std::cout << mse_value << endl;
}
