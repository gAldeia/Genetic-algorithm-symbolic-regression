//node.cpp
#include <random>
#include <cstdlib>
#include <iostream>

#include "../headers/node.hpp"


using namespace utils;


    //--------------------CONSTRUTOR E DESTRUTOR--------------------------//

Node::Node(bool grow, int maxDepth, int numberOfXs){

    //construtor, que recebe se deve construir a árvore no modo growStyle
    //(caso falso, constrói no modo fullStyle). maxDepth determina a pro-
    //fundidade máxima que a subárvore pode assumir. numberOfXs é nece-
    //sário para que o construtor saiba quantas variáveis existem e possa
    //criar este mesmo número de diferentes variáveis nas folhas.
    //por padrão, grow = false, maxDepth = 0, numberOfXs = 1.

    this->numberOfXs = numberOfXs;
    this->maxDepth = maxDepth;

    right = NULL;
    left = NULL;

    if (grow) growStyle();
    else      fullStyle();
}

Node::~Node(){
    
    //destrutor, que recursivamente deleta o nó e todos os seus filhos.

    if (left)  delete left;
    if (right) delete right;
}


    //------------ESTILOS DE CRIAÇÃO DE ÁRVORES DE EXPRESSÕES-------------//

void Node::growStyle(){

    //estilo de crescimento aleatório, que funciona da seguinte forma:
    //enquanto ainda há profundidade para as subárvores, não restringe
    //o tipo que o nó pode ser. Quando chega na profundidade máxima,
    //só cria folhas.

    if (maxDepth>1){
        tipo = random()%SIZETYPE;
        
        if      (tipo==CTE)  makeThisCte();
        else if (tipo==VAR)  makeThisVar();
        else if (tipo==FUN1) makeThisFunc1(true);
        else                 makeThisFunc2(true); //tipo==FUN2
    }
    else {
        tipo = random()%2;

        if (tipo==CTE) makeThisCte();
        else           makeThisVar(); //tipo==VAR
    }
}

void Node::fullStyle(){

    //estilo de crescimento que gera sempre uma árvore binária completa
    //(salvo casos onde são sorteadas funções de 1 parâmetro, tendo
    //apenas um filho, e não dois).

    if (maxDepth>1){
        tipo = random()%2 + 2;

        if (tipo==FUN1) makeThisFunc1(false);
        else            makeThisFunc2(false); //tipo==FUN2 
    }
    else {
        tipo = random()%2;

        if (tipo==CTE) makeThisCte();
        else           makeThisVar(); //tipo==VAR
    }
}


    //----------FUNÇÕES AJUSTADORAS DE VALORES DA ÁRVORE------------------//

void Node::makeThisVar(){

    //função que ajusta valores do nó para ser uma variável. Sorteia um
    //índice de x para os n numberOfXs, deleta e "nulla" os ponteiros.

    tipo = VAR;

    C.idX = random()%numberOfXs;

    if (left) delete left;
    if (right) delete right;

    left = NULL;
    right = NULL;
}

void Node::makeThisCte(){

    //ajusta os valores do nó para ser uma constante. Atribui um valor de
    // 0 a 9 para o nó, deleta e "nulla" os ponteiros.

    tipo = CTE;

    C.value = random()%10;

    if (left) delete left;
    if (right) delete right;

    left = NULL;
    right = NULL;
}

void Node::makeThisFunc1(bool grow){

    //ajusta os valores do nó para ser uma função de 1 parâmetro. A fun-
    //ção é sorteada dentro do utils, e por padrão o filho criado será na 
    //direita (isso não faria diferença aqui se fosse na esquerda), mas
    //as funções do programa estão preparadas para lidar com casos onde
    //a subárvore foi criada no lado esquerdo. chama recursivamente
    //o construtor para que a árvore não fique incompleta.

    tipo = FUN1;

    C.function = random() % SIZEFUNC1;

    if (!right)
        right = new Node(grow, maxDepth-1, numberOfXs);
    if (left) delete left;    
    
    left = NULL;
}

void Node::makeThisFunc2(bool grow){

    //ajusta os valores do nó para ser uma função de 2 parâmetros. A
    //função é sorteada dentro do utils. Chama recursivamente o cons-
    //trutor dos dois filhos para que a árvore não fique incompleta.

    tipo = FUN2;

    C.function = random() % SIZEFUNC2;

    if (!right)
        right = new Node(grow, maxDepth-1, numberOfXs);
    if (!left)
        left  = new Node(grow, maxDepth-1, numberOfXs);
}

void Node::copyInformation(Node *original){
    original->tipo = this->tipo;
    original->numberOfXs = this->numberOfXs;
    original->maxDepth = this->maxDepth;

    if (tipo==VAR)
        original->C.idX = this->C.idX;
    else if (tipo==CTE)
        original->C.value = this->C.value;
    else if (tipo==FUN1)
        original->C.function = this->C.function;
    else //tipo==FUN2
        original->C.function = this->C.function;
}

    //----------------FUNÇÕES DE UTILIDADE GERAL--------------------------//

double Node::eval(DataPoint p) {
    
    //calcula o valor que a expressão retorna quando tem como valores
    //para suas n variáveis os valores do DataPoint.x (vector<double>).

    if (this->tipo==VAR){
        return p.x[C.idX];
    } else if(this->tipo==CTE) {
        return C.value;
    } else if (this->tipo==FUN1){
        if (left)
            return func1_solver(C.function, left->eval(p));
        else
            return func1_solver(C.function, right->eval(p));
    } else //this->tipo==FUN2
        return func2_solver(C.function, left->eval(p), right->eval(p));
}

void Node::print_node_d(){
    
    //imprime a árvore recursivamente.

    if (tipo==FUN2){
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
        }

        right->print_node_d();
        std::cout << ")";
    }
    else if (tipo==CTE)
        std::cout << this->C.value;
    else if (tipo==VAR)
        std::cout << "x" << C.idX;
    else{ //tipo==FUN2
        switch(C.function){
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
        }
        right->print_node_d();
        std::cout << ")";
    }
}

void Node::println_node_d(){

    //quebra uma linha após imprimir a expressão

    print_node_d();
    std::cout << std::endl;
}

Node *Node::get_copy(){
    
    //cria um novo Node, deleta seus filhos e ajusta todos os seus parâ-
    //metros para que seja um ponteiro para uma cópia idêntica do nó que
    //invocou o método.

    Node *aux = new Node(false, 0, 1); 

    aux->tipo = this->tipo;
    aux->numberOfXs = this->numberOfXs;
    aux->maxDepth = this->maxDepth;

    if (tipo==VAR){
        aux->C.idX = this->C.idX;
    }
    else if (tipo==CTE){
        aux->C.value = this->C.value;
    }
    else if (tipo==FUN1){
        aux->C.function = this->C.function;

        if (right) aux->right = this->right->get_copy();
        else       aux->left  = this->left->get_copy();
    }
    else { //tipo==FUN2
        aux->C.function = this->C.function;

        aux->left  = this->left->get_copy();
        aux->right = this->right->get_copy();
    }
    return aux;
}

int Node::get_type(){

    //retorna o tipo do nó. útil para funções da classe individual, já
    //que o tipo é uma variável privada.

    return this->tipo;
}

void Node::set_right(Node *nRight){
    if (right)
        delete right;
    right = nRight;
}

void Node::set_left(Node *nLeft){
    if (left)
        delete left;
    left = nLeft;
}

Node *Node::get_right(){
    return this->right;
}

Node *Node::get_left(){
    return this->left;
}
