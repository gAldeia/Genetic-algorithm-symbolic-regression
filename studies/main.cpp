//----------------------------------------------------------------------------//
//arquivo referencia para alguns tópicos de C/C++, tratanto temas referentes a:
//structs, ponteiros, operadores de ponteiros (*, &, ->), entrada e saída.
//a linguagem C/C++ é uma linguagem "top-down", então tudo que você usa nela
//deve ter sido implementado (ou ao menos declarado) antes da utilização.
//----------------------------------------------------------------------------//


#include <iostream>       //biblioteca para entrada e saida (cin e cout)
#include <string>         //biblioteca para utilizar strings
#include <stack>          //biblioteca para utilizar a estrutura de dados pilha
#include <cstdlib>        //biblioteca da linguagem C, que contém o random()

using namespace std;      //"torna os simbolos das bibliotecas padrões visíveis"


//----------------------------------------------------------------------------//
//IMPLEMENTAÇÃO DOS CONJUNTOS E FUNÇÕES QUE OPERAM SOBRE ELES-----------------//
//----------------------------------------------------------------------------//
string operators[4] = {"*", "-", "+", "/"};  //array que contém os operadores
string terminators[4] = {"x", "y", "1.0", "2.0"};  //array dos terminais


//1o mandamento do fabrício: nomes de variáveis e métodos: ou tudo em inglês 
//                           ou tudo em português.
//2o mandamento do fabrício: nomes de métodos -> usar ações.
string get_random_operator(){
    //função que retorna um operador aleatório.

    return operators[random()%4];
}


string get_random_terminator(){
    //função que retorna um terminal aleatório.

    return terminators[random()%4];
}


string get_random_everything(){
    //função que retorna um elemento de qualquer um dos conjuntos. para evitar
    //arvores monstruosas, a probabilidade de retornar um terminal é maior.

    if (random()%10>7)
        return get_random_operator();
    else   
        return get_random_terminator();
}


//----------------------------------------------------------------------------//
//IMPLEMENTAÇÃO DO NOVO TIPO DE DADOS "NODE"----------------------------------//
//----------------------------------------------------------------------------//
typedef struct node {

    //defino aqui uma estrutura chamada node, que tem ponteiros para seus filhos.
    //o typedef elimina a necessidade de declarar variaveis do tipo node usando
    //o prefixo struct. Uma struct é uma declaração de um novo tipo primitivo de
    //dados. Structs são "precursores" de classes: classes possuem métodos e 
    //atributos, enquanto structs possuem apenas atributos. A vantagem de traba_
    //lhar com structs agora é que nos livramos de complicações com coisas espe_
    //cíficas de classes, como: construtor, destrutor, encapsulamento, etc.

    string value;

    //um ponteiro para uma variável é declarado: 
    //  <tipo de variável> *<id>
    //para acessar os atributos de uma struct, usamos:
    //  <nome-struct>.<nome-atributo>
    //Quando nossa struct é na verdade um ponteiro para uma struct, é necessário
    //resolver o endereço antes:
    //  *<nome-struct>.<nome-atributo>
    //ou usar o operador "->":
    //  <nome-struct>-><nome-atributo>
    //resumindo:
    //  O operador '&' retorna o endereço da variável;
    //  O operador '*' quando usado na declaração, cria um ponteiro para o tipo
    //      de variável declarada.
    //  O operador '*' quando usado como prefixo numa variável resolve o
    //      endereço daquela variável (a variável deve ser um ponteiro)
    //  O operador '->' é usado para omitir o operador '*' no acesso de atribu_
    //      tos de structs (e classes)
    //OBS: um array[] é sempre um ponteiro implícito.

    //OBS 2: (me disseram que) é uma boa prática, sempre que criar ponteiros,
    //inicializá-los com "NULL".
    node *leftChild = NULL;
    node *rightChild = NULL;

} node;


//3o mandamento do fabrício: métodos de debug tem um sufixo "_d".
void print_node_d(node *root){

    //função que imprime um nó recursivamente.

    //Aqui um exemplo de como eu pensei para percorrer as árvores binárias:
    //como cada nó guarda uma referencia para seus dois filhos, acessar a árvore
    //de forma recursiva elimina a necessidade de uma referencia para o pai, e
    //pode ser feito de forma simples, já que a chamada fica aberta até terminar
    //as chamadas recursivas.

    //OBS: uma passagem de parâmetros por referencia em C/C++ é feita passando
    //o ponteiro que aponta para a região de memória da variável. Então, neste
    //caso, está sendo passado o endereço da raiz da árvore.

    cout << "(";
    if (root->leftChild)
        print_node_d(root->leftChild);
    
    cout << root->value;

    if (root->rightChild)
        print_node_d(root->rightChild);
    
    cout << ")";
}


node *generate_tree(){

    //essa função é um "construtor": ela cria uma árvore de expressão e retorna
    //um ponteiro para seu endereço na memória.

    //declarando um node na heap. o operador new retorna um endereço de memória,
    //então seu retorno deve ser armazenado num ponteiro para o tipo de variável.
    //o operador new pode acabar retornando NULL caso o SO não forneça nenhuma
    //memória para o programa, então é bom fazer uma verificação no ponteiro
    //antes de começar a manipulá-lo.
    node *root = new node;

    //um ponteiro quando usado como operação lógica retorna verdadeiro caso
    //seja diferente de NULL;
    if (!root)
        return NULL;

    root->value = get_random_everything();

    if (root->value=="+"||root->value=="-"||root->value=="*"||root->value=="/"){

        //se for criado um terminal, a construção para por aí, caso contrário,
        //se for um operador, é necessário ter 2 números para operar em cima,
        //então, chamo recursivamente o construtor para os ponteiros dos filhos    

        root->leftChild = generate_tree();
        root->rightChild = generate_tree();
    }
    return root;
}


void destruct_tree(node *root){

    //essa função funciona como um "destrutor". quando alocamos memória para uma
    //variável devemos sempre liberá-la após o uso. em Java, o garbage collector
    //faz esse papel, mas em C/C++ o programador precisa ter esse controle.
    //todo new deve casar com um delete.
    //Essa função também opera sobre a árvore recursivamente, então quando
    //um nó é passado para ela, este nó e todos os seus filhos são deletados.
    //é importante ressaltar também que é necessário passar o mesmo ponteiro
    //que foi retornado pelo new para o delete. caso vc faça:
    //  int *i = new int;
    //  i++;
    //  delete i;
    //seu programa explode, pois vc incrementou o endereço e tentou deletar
    //um endereço diferente do original.

    if (root->leftChild)
        destruct_tree(root->leftChild);
    if (root->rightChild)
        destruct_tree(root->rightChild);
    delete root;
}


//----------------------------------------------------------------------------//
//MÉTODO PRINCIPAL -----------------------------------------------------------//
//----------------------------------------------------------------------------//
int main(){

    int i;

    //declarando um array de nós na stack. a stack é um pedaço de memória muito
    //limitado que é alocado para o programa quando ele começa a executar.
    //como as árvores podem assumir grandes tamanhos e pode ser interessante
    //ter grandes populações, as vezes é necessário mais memória do que a stack
    //pode oferecer, sendo necessário usar o operador new.
    node *pop[15];

    //colocando o horário do computador como seed do random, para que o compor_
    //tamento do código não seja sempre igual em todas as execuções (os números
    //gerados pelo random() são pseudo-aleatórios).
    srand(time(NULL));

    //percorro o array inteiro da população, inicializando cada indivíduo.
    for (i=0; i<15; i++)
        pop[i] = generate_tree();

    //imprimo todos os indivíduos que foram criados na população inicial
    for (i=0; i<15; i++){
        print_node_d(pop[i]);
        cout << endl;
    }

    //libero a memoria alocada. todo new deve casar com um delete!
    for (i=0; i<15; i++)
        destruct_tree(pop[i]);

    return 0;
}
