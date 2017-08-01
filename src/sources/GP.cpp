//GP.cpp
#include <cstdlib>
#include <iostream>
#include <math.h>

#include "../headers/GP.hpp"


using namespace utils;


    //--------------------CONSTRUTOR E DESTRUTOR--------------------------//

GP::GP(int popSize, int maxDepth, int numberOfXs){

    //construtor salva internamente as configurações da população e
    //chama o método que cria a população ramped_halfhalf
    this->popSize = popSize;
    this->maxDepth = maxDepth;
    this->numberOfXs = numberOfXs;

    ramped_halfhalf();

    this->bestOfAllTimes = population[0]->get_copy();
}

GP::~GP(){

    //destrutor. precisa limpar o conjunto inteiro de individuos da
    //população. o pop_back chama o destrutor dos itens retirados
    //automaticamente.

    for(int i=population.size() -1; i>=0; i--) {
        population.pop_back();
    }
}


    //---------------MÉTODOS DE MANIPULAÇÃO DA POPULAÇÃO//----------------//

void GP::ramped_halfhalf(){

    //cria a população no modo ramped_halfhalf. Nesse esquema, metade
    //da população é criada no estilo grow e metade no estilo full; e
    //a cada N/5 individuos a profundidade máxima é aumentada em 1.
    int auxMaxDepth = this->maxDepth;

    for (int i=1; i< (popSize+1); i++){
        population.push_back(new Individual(i%2==0, auxMaxDepth, numberOfXs));
        if (i % (popSize/5)==0) auxMaxDepth++;
    }
}

void GP::calculate_fitness(std::vector<utils::DataPoint> points){

    //recebe o vector que contém os pontos utilizados no fitness e 
    //atualiza os valores dos fitness de todos os individuos.

    for (int i=0; i<popSize; i++){
        population[i]->fitness(points);
        if (population[i]->get_fitness() < bestOfAllTimes->get_fitness()){
            delete bestOfAllTimes;
            bestOfAllTimes = population[i]->get_copy();
        }
    }
}    

void GP::mutate_population(double mutation_rate){
    for (int i=0; i<popSize; i++){
        population[i]->mutation(mutation_rate);
    }
}

void GP::tournament_selection_tester(std::vector<utils::DataPoint> points){
    //tournament de teste

    vector<Individual *> selectedPop;
    vector<Individual *> Pfilhos;

    int auxMaxDepth = this->maxDepth;

    for (int i=1; i< (popSize+1); i++){
        Pfilhos.push_back(new Individual(i%2==0, auxMaxDepth, numberOfXs));
        if (i % (popSize/5)==0) auxMaxDepth++;
    }

    calculate_fitness(points);

    for (int i=0; i<popSize; i++){
        Pfilhos[i]->fitness(points);
    }

    for (int i=0; i<popSize; i++){

        int index1, index2;
        double fit1, fit2;

        do {
            index1 = random()% population.size();
            index2 = random()% Pfilhos.size();

            fit1 = population[index1]->get_fitness();
            fit2 = Pfilhos[index2]->get_fitness();
        } while ( (fit1 !=fit1) && (fit2 != fit2) );

        if (fit1<fit2)
            selectedPop.push_back(population[index1]->get_copy());
        else
            selectedPop.push_back(Pfilhos[index2]->get_copy());
    }
    population.clear();
    Pfilhos.clear();

    for (int i=0; i<popSize; i++){
        population.push_back(selectedPop[i]->get_copy());
    }
    selectedPop.clear();
}

void GP::tournament_selection(std::vector<utils::DataPoint> points){
    vector<Individual *> selectedPop;
    
    calculate_fitness(points);

    for (int i=0; i<popSize; i++){

        int index1, index2;
        double fit1, fit2;

        do {
            index1 = random()% population.size();
            index2 = random()% population.size();

            fit1 = population[index1]->get_fitness();
            fit2 = population[index2]->get_fitness();
        } while ( (fit1 !=fit1) && (fit2 != fit2) );

        if (fit1<fit2)
            selectedPop.push_back(population[index1]->get_copy());
        else
            selectedPop.push_back(population[index2]->get_copy());
    }
    population.clear();

    for (int i=0; i<popSize; i++){
        population.push_back(selectedPop[i]->get_copy());
    }
    selectedPop.clear();
}

void GP::crossover_halfhalf(double crossover_rate){
    vector<Individual *> crossedPop;
    
    while (crossedPop.size()<popSize){
        crossedPop.push_back(population[random()%popSize]->crossover(crossover_rate, population[random()%popSize]));
    }

    population.clear();

    for (int i=0; i<popSize; i++){
        population.push_back(crossedPop[i]->get_copy());
    }
    crossedPop.clear();
}

    //----------------------MÉTODOS DE DEBUG------------------------------//

void GP::print_GP_d(){

    //imprime a expressão de cada um dos individuos da população.

    for (int i=0; i<population.size(); i++){
        population[i]->print_expression_d();
        std::cout << std::endl;
    }
}

void GP::print_GP_fitness_d(){

    //imprime o fitness de daca um dos individuos da população.

    for (int i=0; i<popSize; i++){
        std::cout << population[i]->get_fitness() << std::endl;
    }
}

void GP::print_GP_best_fitness_d(){

    double best_mse = this->population[0]->get_fitness();
    int best_eq = 0;

    for (int i=1; i<popSize; i++){
        if (population[i]->get_fitness() < best_mse) {
            best_mse = population[i]->get_fitness();
            best_eq = i ;
        }
    }
    cout << best_mse << "; expressão: ";
    population[best_eq]->expression->print_node_d();
    cout << endl;
}

void GP::printAndCompare_GP_bestOfAllTimes(std::vector<utils::DataPoint> points){
    cout << "O melhor de todos:";
    bestOfAllTimes->print_expression_d();
    cout << "VALOR DA ENTRADA\tVALOR DO MELHOR DE TODOS OS TEMPOS" << endl;
    for (int i=0; i<points.size(); i++){
        cout << points[i].y << "\t" << bestOfAllTimes->expression->eval(points[i]) << endl;
    }
}
