#ifndef _INDIVIDUAL_H
#define _INDIVIDUAL_H

//#include "individual.cpp"
#include <vector>

class Specimen{
    
    private:
        Node *root; //deve ser criado no construtor 
                    //(deve herdar node ou ter um
                    //ponteiro? não sei. acho que a 
                    //vantagem do ponteiro é que o 
                    //get_copy fica mais fácil de ser
                    //utilizado)

    public:
        Specimen();
        ~Specimen();

        crossover(double crossover_rate);
        mutation(double mutation_rate);
        fitness(vector<double> x); //mse
};

#endif
