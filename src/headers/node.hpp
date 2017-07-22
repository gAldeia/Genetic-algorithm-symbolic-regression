//node.hpp
#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include "utils.hpp"


using namespace utils;


class Node{
    private:
        union Content{
            double idX;      //guarda o índice do var(depende de numberOfXs)
            double value;    //constante sorteada de 0-9
            int    function; //func1 ou func2
        };

        Content C;           //union que guarda o valor do nó
        
        int tipo;            //recebe o índice do content
        int numberOfXs;      //número de xn que a árvore pode criar
        int maxDepth;        //maior profundidade que sua subárvore pode ter

        Node *left;
        Node *right;

        void makeThisVar();
        void makeThisCte();
        void makeThisFunc1(bool grow);
        void makeThisFunc2(bool grow);

        void growStyle();
        void fullStyle();        

    public:
        Node(bool grow = true, int maxDepth = 0, int numberOfXs = 1);
        ~Node();

        Node * get_copy();
        int    get_type();
        void   print_node_d();
        void   println_node_d();
        double eval(DataPoint p);
};

#endif
