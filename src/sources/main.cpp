#include <iostream>
#include <vector>

#include "../headers/GP.hpp"


int main() {

    int n_var;

    std::cout << "\nFuncao de quantas variaveis?\n";
    std::cin >> n_var;

    std::vector<utils::DataPoint> points = utils::csvToDP(false, n_var);

    /******************** TESTES ********************/

    int j, i;

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

    srand(time(NULL));

    GP population(500, 4, n_var);

    for (i=0; i<50; i++){
        std::cout << "GERAÇÃO " << i << ": ";
        population.mutate_population(10);   
        population.crossover_halfhalf(40);
        population.tournament_selection(points);     
        population.calculate_fitness(points);
        population.print_GP_best_fitness_d();
    }
    population.printAndCompare_GP_bestOfAllTimes(points);

    std::cout << "FIM" << std::endl;
    return 0;
}
