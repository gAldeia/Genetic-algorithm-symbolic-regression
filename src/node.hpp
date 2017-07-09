#ifndef _NODE_H
#define _NODE_H


class Node{

    private:

        union Content{
            double idX;        //var
            double value;   //const
            int function;   //func1 ou func2
        };
        
        //não sei se enum e union deveriam ser globais ou declaradas dentro
        //do node. A principio, acho que não é de interesse de nenhuma outra
        //função acessar estas informação, mas pode ser que eu esteja enganado.

        Content C;
        int tipo;

        Node *left;
        Node *right;

    public:
        Node();
        ~Node();

        //double eval(vector<double> input);
        void print_node_d();
        Node *get_copy();
};

#endif