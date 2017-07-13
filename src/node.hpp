//node.hpp
#ifndef _NODE_H
#define _NODE_H


#include <vector>


class Node{

    private:
        union Content{
            double idX;     //var
            double value;   //const
            int function;   //func1 ou func2
        };

        Content C;
        int tipo; //recebe o índice do content

        Node *left;
        Node *right;

    public:
        Node(bool copy = false);
        ~Node();

        double eval(double x);
        void print_node_d();
        Node *get_copy();
        int get_type();
};

#endif
