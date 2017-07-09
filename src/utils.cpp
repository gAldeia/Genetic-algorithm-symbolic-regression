#include "utils.hpp"
#include <cmath>

namespace utils{

    // Função Soma
    double add(double v1, double v2) {

        return (v1 + v2);
    }


    // Função Subtração
    double sub(double v1, double v2) {

        return (v1 - v2);
    }


    // Função Multiplicação
    double mult(double v1, double v2) {

        return (v1 * v2);
    }


    // Função Divisão
    double div(double v1, double v2) {

        if (v2 == 0) {
            return 0;   //Padrão
        }
        else {
            return (v1 / v2);
        } 
    }

    // Função Potência
    double pow(double v1, double v2) {

        if ((v1 == 0)&&(v2 == 0)) {
            return 0;   //Padrão - Equivalente matemático a 0/0
        }
        else {
            return pow(v1, v2);
        }    
    }

    // Função Exponencial (e^v)
    double exp(double v) {

        return (exp(v));
    }

    // Função Raiz Quadrada
    double sqrt(double v) {

        if (v < 0) {
            return 0;
        }
        else {
            return (sqrt(v));
        }
    }

    // Função Logaritmo Neperiano
    double ln(double v) {

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
    double sin(double v) {

        return (sin(rad_to_degrees(v)));
    }


    // Função Cosseno
    double cos(double v) {

        return (cos(rad_to_degrees(v)));
    }


    // Função Tangente
    double tan(double v) {

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
                return ln(v);
            case EXP:
                return exp(v);
            case SQRT:
                return sqrt(v);
            case SIN:
                return sin(v);
            case COS:
                return cos(v);
            case TAN:
                return tan(v);
        }
    }

    double func2_solver(int F_id, double v1, double v2) {
        
        switch (F_id) {
            case ADD:
                return add(v1, v2);
            case SUB:
                return sub(v1, v2);
            case MULT:
                return mult(v1, v2);
            case DIV:
                return div(v1, v2);
            case POW:
                return pow(v1, v2);
        }
    }
}