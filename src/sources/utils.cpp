//utils.cpp
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include "../headers/utils.hpp"


namespace utils{

    DataPoint::DataPoint(std::vector<double> x, double y = 0.0){
        
        if (x.size()==0){
            this->x.push_back(0.0);
        }
        else {
            for(int i=0; i<x.size(); i++){
                this->x.push_back(x.at(i));
            }
        }

        this->y = y;
    }

    std::vector<DataPoint> csvToDP(bool label, int n_var) {

        int i, j, n;
        double number;

        std::vector<double> x;
        double y;

        std::vector<DataPoint> points;

        std::string next;
        std::string value;

        std::ifstream DATA("./input/data.csv");
        if (!DATA.is_open()) {
            std::cout << "ERROR openning the file\n" << std::endl;
        }

        if (label) {
            std::string labels;
            getline(DATA, labels, '\n');    //Eliminar linha de labels
        }


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

            getline(DATA, next, '\n');
            std::stringstream(next) >> number;
            x.push_back(number);

            next = "";

            DataPoint point (x,y);

            points.push_back(point);

            x.resize(0);
        }

        DATA.close();

        return points;
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

    //Função Potência
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

    //Converter radianos em graus para poder utilizar as funções trigonométricas
    double rad_to_degrees(double v) {
        
        double V = ((v*180)/(M_PI));    //Transforma o valor de entrada para graus
        if ((V >= 360) || (V <= -360)) V = (int)V%360;
        if (V < 0) V = 360+V;
        return V;
        
    }

    //Função Seno
    double uSin(double v) {

        return (sin(rad_to_degrees(v)));
    }

    //Função Cosseno
    double uCos(double v) {

        return (cos(rad_to_degrees(v)));
    }

    //Função Tangente
    double uTan(double v) {

        double V = rad_to_degrees(v);

        if ((V == 90)||(V == 270))
            return 0;
        else
            return (tan(V));
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
                return tan(v);
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
