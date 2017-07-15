//individual.cpp
#include <vector>
#include <cstdlib>
#include <iostream>

#include "individual.hpp"
#include "utils.hpp"


Individual::Individual(){
    expression = new Node();
}

Individual::~Individual(){
    delete expression;
}

Node *Individual::crossover(double crossover_rate, Individual parent){

}

void Individual::mutation(double mutation_rate){

    double rate = mutation_rate*100;

    if (random()%100<rate){
        int new_tipo = random() %utils::SIZETYPE;

        std::cout << "new tipo: " << new_tipo << std::endl;

        switch (new_tipo){
            case utils::VAR:
                expression->set_C(utils::VAR, random()%2);
                break;
            case utils::CTE:
                expression->set_C(utils::CTE, random()%10);
                break;
            case utils::FUN1:
                expression->set_C(utils::FUN1, random()%utils::SIZEFUNC1);
                break;
            case utils::FUN2:
                expression->set_C(utils::FUN2, random()%utils::SIZEFUNC2);
                break;
        }
    }
}

double Individual::fitness(std::vector<utils::DataPoint> points){
   
    double mse = 0.0;
    
    for(int i=0; i<points.size(); i++){
        mse += utils::uPow((expression->eval(points[i])-points[i].y ), 2);
    }
    
    this->mse_value = utils::uSqrt(mse/(double)points.size());
    
    return this->mse_value;
}

void Individual::print_expression_d(){
    expression->print_node_d();
}
