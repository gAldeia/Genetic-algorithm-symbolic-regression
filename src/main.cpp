#include <iostream>
#include <fstream>
#include <vector>
#include "./headers/GP.hpp"
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>


int main() {

    int i, j, n, n_var, v_size;
    double number;

    std::vector<double> x;
    double y;
    std::vector<utils::DataPoint> points;

    std::string next;
    std::string value;

    /********************** RÓTULOS **********************/
    std::string labels;
    bool label;
    char lab;
    std::cout << "O arquivo contem rotulos?\n(S ou N)\n";
    std::cin >> lab;
    if ((lab == 'S')||(lab == 's')) label = true;
    else label = false;     // Caso a resposta seja outra
    /*****************************************************/

    std::cout << "\nFuncao de quantas variaveis?\n";
    std::cin >> n_var;

    std::ifstream DATA ("data.csv");
    if (!(DATA.is_open())) {
        std::cout << "ERROR: File Open\nPlease, close the file and try again.\n" << std::endl;
    }


    while (DATA.good()) {

        if (label) {                        //////////////////////////////
            getline(DATA, labels, '\n');    // Eliminar linha de labels //
            label = false;                  //        (caso haja)       //
        }                                   //////////////////////////////

        getline(DATA, value, ' ');
        std::stringstream(value) >> y;

        value = "";

        for (i=0; i<n_var-1; i++) {
            getline(DATA, value, ' ');
            std::stringstream(value) >> number;
            x.push_back(number);
            value = "";
        }

        getline(DATA, next, '\n');
        std::stringstream(next) >> number;
        x.push_back(number);

        next = "";

        utils::DataPoint point (x,y);

        points.push_back(point);

        x.resize(0);

        std::cout << "\n";

    }

    DATA.close();


    /******************** TESTES ********************/

    std::cout << "Y\t";
    for (j=1; j<=points[0].x.size(); j++) {

        std::cout << "x" << j << "\t";

    }
    std::cout << "\n";


    for (i=0; i<points.size()-1; i++) {

        std::cout << points[i].y << "\t";
        for (j=0; j<(points[i].x).size(); j++) {
            std::cout << points[i].x[j] << "\t";
        }
        std::cout << "\n";
    }

    /***********************************************/
    GP population(100, 2, n_var);

    population.print_GP_d();
    population.calculate_fitness(points);
    population.print_GP_fitness_d();

    return 0;

}
