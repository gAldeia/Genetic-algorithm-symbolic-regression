//main.cpp
#include <iostream>
#include <cstdlib>
#include <vector>

#include "utils.hpp"
#include "individual.hpp"


using namespace std;


int main(){

    srand(time(NULL));

    //leitura da entrada
    vector<utils::DataPoint> points;
    
    double x1, x2;
    double y;

    for (int i=0; i<1; i++){
        cin >> x1;
        cin >> y;
        vector<double> x = {x1};
        utils::DataPoint p(x, y);
        cout << p.x[0] << endl;
        points.push_back(p);
    }

    //criação de um individuo para testes
    //obs: o construtor recebe o número de x que a entrada contém, para que
    //o node seja criado conténdo esse mesmo número, incluindo dessa forma
    //todos os possíveis x na criação da árvore.
    Individual *sujeito1 = new Individual(false, 5, 1);
    Individual *sujeito2 = new Individual(true, 5, 1);
    //testa o fitness
    cout << sujeito1->fitness(points) << endl;
    //imprime a expressão para consulta
    sujeito1->print_expression_d();
    cout << endl << endl;

    cout << sujeito2->fitness(points) << endl;
    //imprime a expressão para consulta
    sujeito2->print_expression_d();
    cout << endl;
    
    return 0;
}
