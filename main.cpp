//----------------------------------------------------------------------------//
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>


using namespace std;


//GUARDAR FUNÇÕES ÚTEIS IMPLEMENTADAS POR NÓS (NÓS != NODES)------------------//
class Useful{

    //se não me engano, static são métodos que podem ser utiliados sem
    //instanciar uma classe.

    public:
        static double func1_solver(int function, double A, double B);
        static double func2_solver(int function, double A, double B);

        static double div(double A, double B);
        static double sum(double A, double B);

        //e assim vai...
};


//CLASSE NODE: CONTÉM SÓ A "INFORMAÇÃO GENÉTICA"------------------------------//
class Node{

    private:
        enum {
            var = 0,
            cte = 1,
            fun1 = 2,
            fun2 = 3
        } Definitions;

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


//----------------------------------------------------------------------------//
int main(){

    return 0;
}

/*

//----------------------------------------------------------------------------//
// Ideias para melhorar a implementação do código principal.
//----------------------------------------------------------------------------//
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>


using namespace std;


//----------------------------------------------------------------------------//
class Number {
    private:
        //vetor que guarda as possíveis variáveis, sorteadas no construtor
        vector<char> variables {'x', 'y'};

        //diz se este número deverá ser tratado como constante ou como variável.
        //é constante, então após inicialização não pode ser alterada
        const bool definedAsConst;

        //armazena o valor numérico number.
        double xValue;
        double yValue;

        //método que sorteia o valor da constante, caso necessário.
        double sort_const(double start, double finale);

    public:
        //construtor void, que deve fazer um tratamento simples caso nada seja
        //especificado
        Number();

        //construtor que de acordo com a entrada (V ou F) prepara o Number para
        //atuar como uma constante ou uma variável. é importante o construtor
        //definir a definedAsConst. é importante saber se será 2 variáveis ou
        //não para não criar Ys na árvore caso não seja, pois pode criar erros.
        Number(bool definedAsConst, bool isTwoVariables);

        //destrutor
        ~Number();

        //sobrecarga do operador '=', para receber o valor de x, caso seja uma
        //variável (uma variável tem que ser apta a mudanças).
        //é preciso que este método faça um tratamento interno para não acabar
        //modificando o valor caso tenha sido declarado como uma constante.
        //v deve ser um vetor de no máximo 2 valores, contendo ou {x} ou {x, y}.
        void operator=(vector<double> *v);
};

//----------------------------------------------------------------------------//
class Function{
    private:
        //conjunto de funções que pode assumir. (operar com string deixa mais
        //legivel que com char)
        vector<string> function_pool {"func1", "func2", "etc"};

        //bool para saber se opera com 1 ou 2 variáveis.
        const bool isTwoVariables;

        //string que guarda a função do nó
        string function;

    public:
        //método que resolve a função, com polimorfismo para funcionar com 1 ou
        //2 variáveis. O solve deve saber operar de acordo com: o número de va-
        //riáveis passadas e a função salva em function.
        double solve(double x);
        double solve(double x, double y);
    
        //construtor void, que deve fazer um tratamento simples caso nada seja
        //especificado
        Function();

        //o construtor sorteia a função que a classe irá assumir, sempre consi-
        //derando se é ou não um nó de duas variáveis.
        Function(bool isTwoVariables);

        ~Function();
};

//----------------------------------------------------------------------------//
class Node {
    private:
        //ponteiros para o número e tipo do nó. O bom de usar ponteiros aqui É
        //que podemos criar o number e function dentro do construtor do Node.
        //o construtor do Node podia sortear se vai ser uma função ou um número
        //e com isso criar um ponteiro para um dos tipos e outro como null. aí,
        //as funções da classe node fazem uma verificação simples para ver
        //o que o nó é e operam com as funções do seu tipo.
        Number *value = NULL;
        Function *func = NULL;

        //variável que guarda sua profundidade.
        int depth;

        //ponteiros para seus filhos.
        Node *left = NULL;
        Node *right = NULL;

    public:
        
        //construtor void, que deve fazer um tratamento simples caso nada seja
        //especificado
        Node();

        //é importante o nó saber se vai ser de duas variáveis ou não, pois ele
        //que irá chamar os construtores de Number e Function. Tudo tem que ser
        //compatível, então ele tem que criar as classes com sabedoria.
        Node(int depth, bool isTwoVariables);

        ~Node();

        //aqui é preciso incorporar alguns métodos já existentes no arquivo
        //principal ou então modificá-los para funcionar com o novo value.

        //essas funções são necessárias para Number e Function pois os membros
        //de Node são privados.
        Number *get_NumberPt();
        Function *get_FunctionPt();
        Node *get_leftPt();
        Node *get_rightPt();
};


//----------------------------------------------------------------------------//
int main(){

    return 0;
}

*/
