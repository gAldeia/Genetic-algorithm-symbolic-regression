//GP.hpp
#ifndef _GP_H
#define _GP_H

#include <vector>

#include "individual.hpp"


using namespace utils;


class GP {
    private:
        vector<Individual *> population; //contém a população
        
        Individual *bestOfAllTimes;

        int popSize;  //são definidos pelo construtor
        int maxDepth;
        int numberOfXs;

        void ramped_halfhalf();
        
    public:
        GP(int popSize = 0, int maxDepth = 2, int numberOfXs = 1);
        ~GP();

        void calculate_fitness(std::vector<DataPoint> points);
        void tournament_selection_tester(std::vector<DataPoint> points);
        void tournament_selection(std::vector<DataPoint> points);
        void mutate_population(double mutation_rate);
        void crossover_halfhalf(double crossover_rate);
        void print_GP_d();
        void print_GP_fitness_d();
        void print_GP_best_fitness_d();
        void printAndCompare_GP_bestOfAllTimes(std::vector<utils::DataPoint> points);
};

#endif
