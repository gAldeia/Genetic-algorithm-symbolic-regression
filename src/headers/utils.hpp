//utils.hpp
#ifndef _UTILS_H
#define _UTILS_H


#include <vector>


namespace utils {

    //Enums utilizados
    enum TYPE{
        VAR,
        CTE,
        FUN1,
        FUN2,
        SIZETYPE //Tamanho do enum TYPE
    };

    enum FUNC1{
        LN,
        EXP,
        SQRT,
        SIN,
        COS,
        TAN,
        SIZEFUNC1 //Tamanho do enum FUNC1
    };

    enum FUNC2{
        ADD,
        SUB,
        MULT,
        DIV,
        POW,
        SIZEFUNC2 //Tamanho do enum FUNC2
    };

    typedef struct DataPoint{
        std::vector<double> x;
        double y;

        DataPoint(std::vector<double> x, double y);
    }DataPoint;

    std::vector<DataPoint> csvToDP(bool label = false, int n_var = 1); 

    //funções solucionadoras
    double func1_solver(int F_id, double v);
    double func2_solver(int F_id, double v1, double v2);

    //função de conversão
    double rad_to_degrees(double v);

    //funções de 2 parâmetros
    double  uDiv(double v1, double v2);
    double  uAdd(double, double);
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
