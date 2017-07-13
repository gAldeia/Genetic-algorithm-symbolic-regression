//individual.cpp
#include <vector>
#include <cstdlib>

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
        //aqui eu sorteio um novo tipo de nó, e com isso um novo valor de C
        //também
        int tipo_anterior = expression->get_type();
        int new_tipo = random() %utils::SIZETYPE;

        if (tipo_anterior==new_tipo) {
            //caso continue igual, sorteia outro valor
        }
        else {
            //caso mude, verifica se é func1 ou 2 e toma as devidas ações
            //ou seja -> ou cria um novo filho ou deleta um para que a árvore 
            //não tenha pedaços que não sejam utilizados ou tenha pedaços
            //faltando.
        }
    }
}

double Individual::fitness(vector< vector<double> > points){
   
    double mse = 0.0;
    
    for(int i=0; i<points.size(); i++){
        mse += utils::uPow((expression->eval(points[0][i])-points[1][i] ), 2);
    }
    
    this->mse_value = utils::uSqrt(mse/(double)points.size());
    
    return this->mse_value;
}

void Individual::print_expression_d(){
    expression->print_node_d();
}
