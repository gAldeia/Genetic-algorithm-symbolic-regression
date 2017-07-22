//GP.hpp
#ifndef _GP_H
#define _GP_H

#include "individual.hpp"

#include <vector>

class GP {
    private:
        vector<Individual *> population;
        
        int popSize;  //são definidos pelo construtor
        int maxDepth;
        int numberOfXs;

        void ramped_halfhalf();
    public:
        GP(int popSize = 0, int maxDepth = 2, int numberOfXs = 1);
        ~GP();

        void calculate_fitness(std::vector<utils::DataPoint> points);

        void print_GP_d();
        void print_GP_fitness_d();
};

#endif
