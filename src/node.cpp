#include "node.hpp"
#include "utils.hpp"

#include <random>
#include <cstdlib>
#include <iostream>

using namespace utils;

//IMPLEMENTAÇÃO DE NODE-------------------------------------------------------//
Node::Node(){
    tipo = random() % SIZETYPE;

    if (tipo==CTE){
        //atribui um valor de 0 a 9 para a variável
        C.value = random()%10;

        //se aqui é variável, é folha, então não terá filhos.
        left = NULL;
        right = NULL;
    }
    else if (tipo==VAR){
        
        C.idX = 0.0;

        //var tbm é folha
        left = NULL;
        right = NULL;
    }
    else if (tipo==FUN1){

        C.function = random() % SIZEFUNC1;

        //por padrão, funções unárias terão filho só na direita. a vantagem de
        //usar só na direita é que facilita a impressão pois não precisamos
        //tratar unário/binário diferentemente.
        right = new Node();
    }
    else if (tipo==FUN2){

        C.function = random() % SIZEFUNC2;

        right = new Node();
        left = new Node();
    }
    else
        std::cout << "ERRO CONSTRUTOR NODE" << std::endl;
}

Node::~Node(){

}

void Node::print_node_d(){
    if (tipo==FUN2){

        //se o nó é func2, sabemos que o nó direito não é nulo (pelo menos não
        //deveria ser)
        std::cout << "(";
        left->print_node_d();

        switch(C.function){
                case ADD:
                    std::cout << "+";
                    break;
                case DIV:
                    std::cout << "/";
                    break;
                case SUB:
                    std::cout << "-";
                    break;
                case MULT:
                    std::cout << "*";
                    break;
                case POW:
                    std::cout << "^";
                    break;
                default:
                    std::cout << "ERRO PRINT NODE D FUN2";
            }
        right->print_node_d();
        std::cout << ")";
    }
    else if (tipo==CTE)
        std::cout << this->C.value;
    else if (tipo==VAR)
        std::cout << "x"; //na hora de imprimir, escreve x
    else{ //ultimo caso possivel é ser fun1
        switch(C.function){ //ln exp, sqrt
            case LN:
                std::cout << "ln(";
                break;
            case EXP:
                std::cout <<"(e^";
                break;
            case SQRT:
                std::cout  << "sqrt(";
                break;
            case SIN:
                std::cout << "sin(";
                break;
            case COS:
                std::cout << "cos(";
                break;
            case TAN:
                std::cout << "tan(";
                break;
            default:
                std::cout << "ERRO PRINT NODE D FUN1";
        }

        right->print_node_d();
        std::cout << ")";
    }
}