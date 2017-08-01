//individual.cpp
#include <vector>
#include <cstdlib>
#include <iostream>
#include <stack>

#include "../headers/individual.hpp"


using namespace utils;


    //--------------------CONSTRUTOR E DESTRUTOR--------------------------//

Individual::Individual(bool grow, int maxDepth, int numberOfXs){

    //construtor. recebe a profundidade máxima, o estilo de crescimento
    //e o número de variáveis que a árvore terá, e chama o construtor da
    //expressão interna.
    expression = new Node(grow, maxDepth, numberOfXs);
}

Individual::~Individual(){

    //destrutor, que deleta o Node *expression, que é alocado
    //dinâmicamente

    delete expression;
}


    //-------------OPERAÇÕES GENÉTICAS SOBRE O INDIVÍDUO------------------//

Individual *Individual::crossover(double crossover_rate, Individual *parent){

    Individual *thisParent = this->get_copy();
    Individual *thatParent = parent->get_copy();

    Node *thisPartition = thisParent->expression;
    Node *parentPartition = thatParent->expression;

    while (thisPartition!=NULL){
        if (thisPartition->get_left()==NULL || thisPartition->get_right()==NULL)
            break;
        if (random()%100 < crossover_rate){
            while (parentPartition!=NULL){
                if (parentPartition->get_left()==NULL || parentPartition->get_right()==NULL)
                    break;
                if (random()%100 < crossover_rate){
                    //é preciso ser uma cópia aqui porque o método de
                    //"setar" ponteiros deleta o ponteiro atual antes
                    //de atribuir o novo
                    thisPartition->set_left(parentPartition->get_left()->get_copy());
                    thisPartition->set_right(parentPartition->get_right()->get_copy());
                    thisPartition->copyInformation(parentPartition);

                    break;
                }
                parentPartition = random()%2==1 ? parentPartition->get_right() : parentPartition->get_left();
            }
            break;
        }
        thisPartition = random()%2==1 ? thisPartition->get_right() : thisPartition->get_left();
    }
    delete thatParent;
    return thisParent;
}

void Individual::mutation(double mutation_rate){

    Node *partition;
    stack<Node *>pilha;

    pilha.push(this->expression);

    while (!pilha.empty()){
        partition = pilha.top();
        pilha.pop();

        if (random()%100 <= mutation_rate){
            switch(random()%utils::SIZETYPE){
                case VAR: //cte fun1 fun2
                    partition->makeThisVar();
                    break;
                case CTE:
                    partition->makeThisCte();
                    break;
                case FUN1:
                    partition->makeThisFunc1(false);
                    break;
                case FUN2:
                    partition->makeThisFunc2(false);
                    break;
                default:
                    std::cout << "Erro mutation" << std::endl;
            }
        }

        if (partition->get_left()!=NULL)  pilha.push(partition->get_left());
        if (partition->get_right()!=NULL) pilha.push(partition->get_right());
    }
}

double Individual::fitness(std::vector<DataPoint> points){
   
    //método que recebe o conjunto de pontos que devem ser testados, e 
    //calcula o mse.

    this->mse_value = 0.0;
    
    for(int i=0; i<points.size(); i++)
        this->mse_value += uPow((expression->eval(points[i])-points[i].y ), 2);
    
    this->mse_value = uSqrt(this->mse_value/(double)points.size());
    
    return this->mse_value;
}

Individual *Individual::get_copy(){
    Individual *aux = new Individual(false, 0, 1);

    aux->expression = this->expression->get_copy();
    aux->mse_value = this->mse_value;

    return aux;
}


    //----------------------MÉTODOS DE DEBUG------------------------------//

void Individual::print_expression_d(){

    expression->println_node_d();
}

double Individual::get_fitness(){
    
    return mse_value;
}
