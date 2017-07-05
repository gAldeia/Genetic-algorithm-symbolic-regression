//----------------------------------------------------------------------------//
#include <iostream>
#include <cstdlib>
#include <vector>


using namespace std;


//GUARDAR FUNÇÕES ÚTEIS IMPLEMENTADAS POR NÓS (NÓS != NODES)------------------//
class Useful{

    public:
        static double func1_solver(int function, double A, double B);
        static double func2_solver(int function, double A, double B);

        static double div(double A, double B);
        static double sum(double A, double B);
        static double sub(double A, double B);
        static double mut(double A, double B);

        static double   sen(double A);
        static double cosen(double A);
};


//CLASSE NODE: CONTÉM SÓ A "INFORMAÇÃO GENÉTICA"------------------------------//
class Node{

    private:
        enum {
            var,
            cte,
            fun1,
            fun2
        } Definition;

        union {
            int idX;        //var
            double value;   //const
            int function;   //func1 ou func2
        } Value;
        
        Node *left;
        Node *right;

    public:
        Node();
        ~Node();

        double eval(vector<double> x);
        void print_node_d();
        Node *get_copy();
};


//CLASSE SPECIMEN: CONTÉM AS OPERAÇÕES SOBRE O "MATERIAL GENÉTICO"------------//
class Specimen : public Node{
    
    //herda NODE

    private:

    public:
        Specimen();
        ~Specimen();

        // crossover();
        // mutation();
        // fitness();
        // etc...
};


//CLASSE QUE FUNCIONA COMO O MEIO AMBIENTE PARA DARWIN------------------------//
class Environment{

    private:
        Specimen *pop;
        int popSize;

    public:
        Environment();
        Environment(int popSize);
        ~Environment();

        void apply_crossover();
        void apply_mutation();
        void apply_fitness();
};


//----------------------------------------------------------------------------//
int main(){

    return 0;
}
