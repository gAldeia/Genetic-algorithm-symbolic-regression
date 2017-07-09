#ifndef _UTILS_H
#define _UTILS_H


namespace utils {
    enum TYPE{
        VAR,
        CTE,
        FUN1,
        FUN2,
        SIZETYPE //sizeof deve ser sempre o último elemento do enum e será
                //utilizado para informar o tamanho do enum.
    };

    enum FUNC1{
        LN,
        EXP,
        SQRT,
        SIN,
        COS,
        TAN,
        SIZEFUNC1
    };

    enum FUNC2{
        ADD,
        SUB,
        MULT,
        DIV,
        POW,
        SIZEFUNC2
    };

    double func1_solver(int F_id, double v);
    double func2_solver(int F_id, double v1, double v2);
    double rad_to_degrees(double v);

    //funções de 2 parâmetros
    double  div(double v1, double v2);
    double  add(double, double);
    double  sub(double v1, double v2);
    double mult(double v1, double v2);
    double  pow(double v1, double v2);

    //funções de 1 parâmetro
    double   sin(double v);
    double   cos(double v);
    double   tan(double v);
    double    ln(double v);
    double   exp(double v);
    double  sqrt(double v);

}
#endif