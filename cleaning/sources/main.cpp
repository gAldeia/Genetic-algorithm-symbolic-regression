/// main.cpp

#include <iostream>
#include <vector>

#include "../headers/GP.hpp"
#include "utils.cpp"
#include "node.cpp"
#include "individual.cpp"
#include "GP.cpp"

int main() {

    int n_var;
    std::string answer;
    bool label;
    std::cout << "\nFuncao de quantas variaveis?\n";
    std::cin >> n_var;
    std::cout << "\nO arquivo contem rotulos?\n";
    std::cin >> answer;
    if ((answer == "S")||(answer == "s")||(answer == "Sim")||(answer == "sim")) {
        label = true;
    }
    else {
        label = false;
    }


    /*
    int popSize, maxDepth, n_generations;
    std::cout << "\nInsira o tamanho da população: ";
    std::cin >> popSize;
    std::cout << "\nInsira a profundidade máxima da árvore: ";
    std::cin >> maxDepth;
    std::cout << "\nInsira o número de gerações: ";
    std::cin >> n_generations;
    double mutation_rate, crossover_rate;
    std::cout << "\nInsira a taxa de mutação: ";
    std::cin >> mutation_rate;
    std::cout << "\nInsira a taxa de crossover: ";
    std::cin >> crossover_rate;
    std::cout << "\n"
    */


    //Coleta de dados, formação de um vector de DataPoints
    std::vector<utils::DataPoint> points = utils::csvToDP(label, n_var);

    /***  IDEIA FUTURA
    std::string path;
    std::cout << "\nOnde estao os dados?";
    std::cin >> path;
    std::vector<utils::DataPoint> points = utils::csvToDP(label, n_var, path);
    ***/

    /***************************** TESTES *****************************/
    int j, i;
    std::cout << "Y\t\t";
    for (j=1; j<=points[0].x.size(); j++) {
        std::cout << "x" << j << "\t\t";
    }
    std::cout << "\n";
    for (i=0; i<points.size()-1; i++) {             ////////////////////
        std::cout << points[i].y << "\t\t";         //  Imprime todos //
        for (j=0; j<(points[i].x).size(); j++) {    //   os pontos    //
            std::cout << points[i].x[j] << "\t\t";  //    coletados   //
        }                                           //    no modelo   //
        std::cout << "\n";                          // y x1 x2 ... xn //
    }                                               ////////////////////
    /******************************************************************/

    srand(time(NULL));

    /*
    GP population(popSize, MaxDepth, n_var);

    for (i=0; i<n_generations; i++) {
        std::cout << "GERACAO " << i << ": ";
        population.mutate_population(mutation_rate);
        population.crossover_halfhalf(crossover_rate);
        population.tournament_selection(points);
        //population.calculate_fitness(points);
        population.print_GP_best_fitness_d();
    }
    */

    GP population(500, 5, n_var);

    for (i=0; i<100; i++) {

        std::cout << "GERACAO " << i << ": ";
        population.mutate_population(70);
        population.crossover_halfhalf(40);
        population.tournament_selection(points);
        population.calculate_fitness(points);
        population.print_GP_best_fitness_d();

    }

    population.printAndCompare_GP_bestOfAllTimes(points);

    std::cout << "FIM" << std::endl;

    return 0;

}
