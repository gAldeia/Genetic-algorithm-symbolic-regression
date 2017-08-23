///utils.hpp

#ifndef _UTILS_H
#define _UTILS_H

#include <vector>
#include <ctime>
#include <cstdlib>

namespace utils {


    /************ Enums utilizados ************/

    // Tipo de Nó
    enum TYPE {
        VAR,     //Variável
        CTE,     //Constante
        FUN1,    //Função com 1 parâmetro
        FUN2,    //Função com 2 parâmetros
        SIZETYPE //Tamanho do enum TYPE
    };

    // Tipos de Funções de 1 parâmetro
    enum FUNC1 {
        LN,       //Logaritmo Natural
        EXP,      //Exponencial (e^x)
        SQRT,     //Raiz Quadrada
        SIN,      //Seno
        COS,      //Cosseno
        TAN,      //Tangengte
        SIZEFUNC1 //Tamanho do enum FUNC1
    };

    // Tipos de Funções de 2 parâmetros
    enum FUNC2 {
        ADD,      //Soma
        SUB,      //Subtração
        MULT,     //Multiplicação
        DIV,      //Divisão
        POW,      //Potenciação
        SIZEFUNC2 //Tamanho do enum FUNC2
    };

    /******************************************/


    /*************** Ponto do gráfico ***************/
    typedef struct DataPoint {

        std::vector<double> x;
        double y;

        DataPoint(std::vector<double> x, double y);

    }DataPoint;
    /************************************************/


    ///Função para a coleta de dados a partir de um arquivo csv
    std::vector<DataPoint> csvToDP(bool label = false, int n_var = 1); // Vector contendo todos os pontos do gráfico


    //funções solucionadoras de expressões
    double func1_solver(int F_id, double v);
    double func2_solver(int F_id, double v1, double v2);

    //funções de 2 parâmetros
    double  uDiv(double v1, double v2);
    double  uAdd(double v1, double v2);
    double  uSub(double v1, double v2);
    double uMult(double v1, double v2);
    double  uPow(double v1, double v2);

    //funções de 1 parâmetro
    double   uSin(double v);
    double   uCos(double v);
    double   uTan(double v);
    double    uLn(double v);
    double   uExp(double v);
    double  uSqrt(double v);

}

#endif
