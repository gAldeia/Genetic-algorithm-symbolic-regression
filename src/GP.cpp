//GP.cpp
#include "GP.hpp"

#include <cstdlib>
#include <iostream>


GP::GP(int popSize, int maxDepth, int numberOfXs){

    this->popSize = popSize;
    this->maxDepth = maxDepth;
    this->numberOfXs = numberOfXs;

    ramped_halfhalf();
}

GP::~GP(){
    for(int i=population.size() -1; i>=0; i--) {
        population.pop_back();
    }
}

void GP::ramped_halfhalf(){

    for (int i=0; i<popSize; i++){
        if (i%2==0)
            population.push_back(new Individual(true, maxDepth, numberOfXs));
        else
            population.push_back(new Individual(false, maxDepth, numberOfXs));
        if (i % (popSize/5)==0)
            this->maxDepth= this->maxDepth + 1;
    }
}
    

void GP::print_GP_d(){
    for (int i=0; i<population.size(); i++){
        population[i]->print_expression_d();
        std::cout << std::endl;
    }
}
