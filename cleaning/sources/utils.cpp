///utils.cpp

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <random>
#include <cmath>

#include "../headers/utils.hpp"

/*** #define PI 3.14159  Eliminável se tirarmos a parte na uTan***/

namespace utils {

    //=================LEITURA DE DADOS E DATAPOINT=======================//

    DataPoint::DataPoint(std::vector<double> x, double y = 0.0) {
        if (x.size() == 0) {
            this->x.push_back(0.0);
        }
        else {
            for (int i=0; i<x.size(); i++) {
                this->x.push_back(x.at(i));
            }
        }
        this->y = y;
    }

    /*********************************************************************************************\
    |***   Função que coleta dados de um arquivo .csv e transforma em um vetor de DataPoints   ***|
    \*********************************************************************************************/
    std::vector<DataPoint> csvToDP(bool label, int n_var) {

        int i, j;
        double number;
        std::string value;

        std::vector<double> x;
        double y;

        std::vector<DataPoint> points;

        std::ifstream DATA("./input/data.csv");
        if (!DATA.is_open()) {
            std::cout << "ERRO NOS DADOS\n" << std::endl;
        }

        //// Eliminar linha de labels ////
        if (label) {
            std::string labels;
            getline(DATA, labels, '\n');
        }
        //////////////////////////////////

        while (DATA.good()) {

            getline(DATA, value, ',');
            std::stringstream(value) >> y;

            value = "";

            for (i=0; i<n_var-1; i++) {
                getline(DATA, value, ',');
                std::stringstream(value) >> number;
                x.push_back(number);
                value = "";
            }
            getline(DATA, value, '\n');
            std::stringstream(value) >> number;
            x.push_back(number);
            value = "";

            DataPoint point (x,y);

            points.push_back(point);

            x.resize(0);

        }

        DATA.close();

        return points;

    }
    /*********************************************************************************************/

    bool fitnessValidation(double number){
        //tentativa de eliminar os "-nan"
        if (number<=0 || number!=number)
            return false;
        return true;
    }

    int rnd(int i, int f){
        //gerador de números aleatórios
        std::random_device generator;
        std::uniform_int_distribution <int> uidist(i, f);
        return uidist(generator);
    }
    

    //=========================FUNÇÕES BINÁRIAS===========================//

    //Função Soma
    double uAdd(double v1, double v2) {
        return (v1 + v2);
    }

    //Função Subtração
    double uSub(double v1, double v2) {
        return (v1 - v2);
    }

    //Função Multiplicação
    double uMult(double v1, double v2) {
        return (v1 * v2);
    }

    //Função Divisão
    double uDiv(double v1, double v2) {
        if (v2 == 0)
            return 0;   //Padrão
        else
            return (v1 / v2);
    }

    //Função Potenciação
    double uPow(double v1, double v2) {
        if ((v1 == 0)&&(v2 == 0))
            return 0;   //Padrão - Equivalente matemático a 0/0
        else
            return pow(v1, v2);
    }


    //==========================FUNÇÕES UNÁRIAS===========================//

    //Função Exponencial (e^v)
    double uExp(double v) {
        return (exp(v));
    }

    //Função Raiz Quadrada
    double uSqrt(double v) {
        if (v < 0)
            return 0;
        else
            return (sqrt(v));
    }

    //Função Logaritmo Neperiano
    double uLn(double v) {
        if (v > 0)
            return (log(v));
        else
            return 0;
    }

    /****************************************************************\
    |***                          Nota:                           ***|
    |***        A função rad_to_degrees foi removida pois         ***|
    |***  as funções trigonométricas recebem ângulos em radianos  ***|
    \****************************************************************/

    //Função Seno
    double uSin(double v) {
        return (sin(v));
    }

    //Função Cosseno
    double uCos(double v) {
        return (cos(v));
    }

    //Função Tangente
    double uTan(double v) {


    // Não sei se é necessário

        /**********************************************************************************\
        |***  Reduzir o ângulo dado para menor que uma volta no círculo trigonométrico  ***|
        |***         para ser possível verificar os casos especiais da tangente         ***|
        \**********************************************************************************

        /*if (v >= 0) {
            while (v >= (2*PI)) {
                v -= 2*PI;
            }
        }
        else {
            while (v < (2*PI)) {
                v += 2*PI;
            }
        }
        if ((v == (PI/2))||(v == (3*(PI/2)))) {
            return 0;   // Mesmo padrão para divisão por 0
        }
        else {
            return (tan(v));
        }*/

            return (tan(v));

    }


    //=====================SOLUCIONADOR DE EQUAÇÕES=======================//

    //Solucionador de equações de aridade 1
    double func1_solver(int F_id, double v) {
        switch (F_id) {
            case LN:
                return uLn(v);
            case EXP:
                return uExp(v);
            case SQRT:
                return uSqrt(v);
            case SIN:
                return uSin(v);
            case COS:
                return uCos(v);
            case TAN:
                return uTan(v);
            default:
                std::cout << "ERRO FUNC1 SOLVER" << std::endl;
                return -1.0;
        }
    }


    //Solucionador de equações de aridaade 2
    double func2_solver(int F_id, double v1, double v2) {
        switch (F_id) {
            case ADD:
                return uAdd(v1, v2);
            case SUB:
                return uSub(v1, v2);
            case MULT:
                return uMult(v1, v2);
            case DIV:
                return uDiv(v1, v2);
            case POW:
                return uPow(v1, v2);
            default:
                std::cout << "ERRO FUNC2 SOLVER" << std::endl;
                return -1.0;
        }
    }

}
