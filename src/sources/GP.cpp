//GP.cpp
#include "../headers/GP.hpp"

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

    for (int i=1; i< (popSize+1); i++){
        population.push_back(new Individual(i%2==0, maxDepth, numberOfXs));
        if (i % (popSize/5)==0) this->maxDepth= this->maxDepth + 1;
    }
}
    

void GP::print_GP_d(){
    for (int i=0; i<population.size(); i++){
        population[i]->print_expression_d();
        std::cout << std::endl;
    }
}


void GP::print_GP_fitness_d(){
    for (int i=0; i<popSize; i++){
        population[i]->print_fitness_d();
    }
}


void GP::calculate_fitness(std::vector<utils::DataPoint> points){
    for (int i=0; i<popSize; i++){
        population[i]->fitness(points);
    }
}
