//node.hpp
#ifndef _NODE_H
#define _NODE_H


#include <vector>

#include "utils.hpp"

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
        Node(bool copy = false, bool grow = true, int maxDepth = 3, int numberOfXs = 1);
        ~Node();

        void growStyle(int maxDepth, int numberOfXs);
        void fullStyle(int maxDepth, int numberOfXs);
        void print_node_d();

        Node *get_copy();
        int get_type();

        void changeNumberOfSubtreesTo(int quantity);

        double eval(utils::DataPoint p);
};

#endif
