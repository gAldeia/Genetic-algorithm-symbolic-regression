#include "utils.hpp"

#include <cmath>
#include <iostream>

namespace utils{

    // Função Soma
    double uAdd(double v1, double v2) {

        return (v1 + v2);
    }


    // Função Subtração
    double uSub(double v1, double v2) {

        return (v1 - v2);
    }


    // Função Multiplicação
    double uMult(double v1, double v2) {

        return (v1 * v2);
    }


    // Função Divisão
    double uDiv(double v1, double v2) {

        if (v2 == 0) {
            return 0;   //Padrão
        }
        else {
            return (v1 / v2);
        } 
    }

    // Função Potência
    double uPow(double v1, double v2) {

        if ((v1 == 0)&&(v2 == 0)) {
            return 0;   //Padrão - Equivalente matemático a 0/0
        }
        else {
            return pow(v1, v2);
        }    
    }

    // Função Exponencial (e^v)
    double uExp(double v) {

        return (exp(v));
    }

    // Função Raiz Quadrada
    double uSqrt(double v) {

        if (v < 0) {
            return 0;
        }
        else {
            return (sqrt(v));
        }
    }

    // Função Logaritmo Neperiano
    double uLn(double v) {

        if (v > 0) {
            return (log(v));
        }
        else {
            return 0;
        }
    }

    // Converter radianos em graus para poder utilizar as funções trigonométricas
    double rad_to_degrees(double v) {
        
        double V = ((v*180)/(M_PI));
        while (V > 360) V -= 360;
        while (V < -360) V += 360;
        if (V < 0) V = 360-V;
        return V;
    }

    // Função Seno
    double uSin(double v) {

        return (sin(rad_to_degrees(v)));
    }


    // Função Cosseno
    double uCos(double v) {

        return (cos(rad_to_degrees(v)));
    }


    // Função Tangente
    double uTan(double v) {

        double V = rad_to_degrees(v);
        if ((V == 90)||(V == 270)) {
            return 0;
        }
        else {
            return (tan(V));
        }
    }

    double func1_solver(int F_id, double v) {
        
        switch (F_id) {
            case LN:
                return uLn(v);
                break;
            case EXP:
                return uExp(v);
                break;
            case SQRT:
                return uSqrt(v);
                break;
            case SIN:
                return uSin(v);
                break;
            case COS:
                return uCos(v);
                break;
            case TAN:
                return tan(v);
                break;
            default:
                std::cout << "ERRO FUNC1 SOLVER" << std::endl;
        }
    }

    double func2_solver(int F_id, double v1, double v2) {
        
        switch (F_id) {
            case ADD:
                return uAdd(v1, v2);
                break;
            case SUB:
                return uSub(v1, v2);
                break;
            case MULT:
                return uMult(v1, v2);
                break;
            case DIV:
                return uDiv(v1, v2);
                break;
            case POW:
                return uPow(v1, v2);
                break;
            default:
                std::cout << "ERRO FUNC2 SOLVER" << std::endl;
        }
    }
}
