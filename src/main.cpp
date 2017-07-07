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

        //tipos possíveis para o Node.
        enum Type{
            VAR,
            CTE,
            FUN1,
            FUN2,
            SIZEOF //sizeof deve ser sempre o último elemento do enum e será
                   //utilizado para informar o tamanho do enum.
        };

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



//IMPLEMENTAÇÃO DE USEFUL-----------------------------------------------------//
double Useful::div(double A, double B){
    //a palavra static não vem aqui!
    if (B==0.0)
        return 0.0;
    else
        return A/B;
}



//IMPLEMENTAÇÃO DE NODE-------------------------------------------------------//
Node::Node(){
    tipo = random() % SIZEOF;

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

        //C.function = SEN;

        //por padrão, funções unárias terão filho só na direita. a vantagem de
        //usar só na direita é que facilita a impressão pois não precisamos
        //tratar unário/binário diferentemente.
        right = new Node();
    }
    else if (tipo==FUN2){

        //C.function = SUM;

        right = new Node();
        left = new Node();
    }
    else
        cout << "ERRO CONSTRUTOR NODE" << endl;
}

void Node::print_node_d(){
    if (left!=NULL)
        left->print_node_d();

    if (tipo==CTE)
        cout << this->C.value << endl;
    else if (tipo==VAR)
        cout << this->C.idX << endl;
    else
        cout << this->C.function << endl;

    if (right!=NULL)
        right->print_node_d();
}



//----------------------------------------------------------------------------//
int main(){

    srand(time(NULL));

    Node *root = new Node();

    //exemplo de utilização dos métodos estáticos
    cout << Useful::div(5.0, 2.0) << endl;
    root->print_node_d();
    return 0;
}
