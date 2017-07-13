//main.cpp
#include <iostream>
#include <cstdlib>
#include <vector>

#include "utils.hpp"
#include "individual.hpp"


using namespace std;


int main(){

    srand(time(NULL));

    vector< vector<double> > points;
    vector<double> x;
    vector<double> y;
    
    double temp;
    Individual *sujeito1 = new Individual();


    for (int i=0; i<2; i++){
        cin >> temp;
        x.push_back(temp);
        cin >> temp;
        y.push_back(temp);
    }
    
    points.push_back(x);
    points.push_back(y);
    
    cout << sujeito1->fitness(points) << endl;
    sujeito1->print_expression_d();
    cout << endl;
    
    return 0;
}
