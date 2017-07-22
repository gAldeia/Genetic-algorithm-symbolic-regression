//inputGenerator.cpp
#include <iostream>
#include <cstdlib>

#include "node.hpp"


using namespace std;


double desvio(){
    //retorna um numero double entre -1 e 1
    if (random()%2==0)
        return -(random()%100)*0.01;
    return (random()%100)*0.01;
}


int main(){

    srand(time(NULL));

    //lê o número de linhas que a saída deve ter
    int n;
    cin >> n;

    //gera uma expressão aleatória
    Node *randomExpression = new Node();

    //imprime a expressão
    randomExpression->print_node_d();
    cout << endl;

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            
            //cria x1 e x2 com um pequeno desvio, para tentar simular
            //a imperfeição de medidas em experimentos
            double x1 = i + desvio();
            double x2 = i + desvio();

            //cria um datapoint (o y não interessa aqui, já que é usado só
            //para calcular o mse)
            utils::DataPoint p(x1, x2, 0.0);

            //calcula o y para a expressao, e adiciona a imprecisão também
            double y = randomExpression->eval(p) + desvio();

            //imprime no estilo x1 x2 y, formato que o programa lê as entradas
            cout << x1 << " " << x2 << " " << y << endl;
        }
    }

    return 0;
}
