#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

//#include "individual.cpp"
#include <vector>

class Individual{
    
    private:
        Node *expression; //deve ser criado no construtor 
                    //(deve herdar node ou ter um
                    //ponteiro? não sei. acho que a 
                    //vantagem do ponteiro é que o 
                    //get_copy fica mais fácil de ser
                    //utilizado)

    public:
        Individual();
        ~Individual();

        Node *crossover(double crossover_rate, Individual parent);
        void mutation(double mutation_rate);
        double fitness(vector<double> x); //mse
};

#endif
