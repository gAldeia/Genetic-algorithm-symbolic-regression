# Genetic-algorithm-symbolic-regression

algoritmos desenvolvidos durante o aprendizado de programação genética e regressão simbólica.

---

## O projeto

A ideia principal do projeto era criar uma classe que gerenciasse uma população de árvores binárias. As árvores binárias formam expressões matemáticas, com operadores, variáveis e constantes.

---

### BinaryTree.hpp

Contém a implementação de todo o código. Consiste em duas classes:


node:

    É a estrutura fundamental da composição das árvores binárias.
    Contém todos os métodos necessários para trabalhar com as árvores binárias.
    

population:

    É uma classe que gerencia a população como um todo.
    Funciona como a criadora de eventos na população, invocando o crossover, mutação e outras 
    operações em cada um dos indivíduos.

---

### main.cpp

Aqui está definido o alvo da regressão simbólica, assim como os fatores necessários para a execução.

---

## Testes de execução

O exemplo a baixo é resultado da execução do algoritmo para os pontos (pontos alvo): 

    (0, 1), (1, 2), (2, 4), (3, 8), (4, 16), (5, 32), (6, 64)

O algoritmo basicamente tentará encontrar uma função que se aproxime dos pontos passados como alvo. Os pontos foram tirados da função f(x) = 2^x. No exemplo utilizado, o programa encontrou com êxito a função que deu origem aos pontos.

O resultado, usando uma população de 50 árvores, foi o seguinte:

    ACHOU: ((1+1)^x); na geração 256
    ((1+1)^x)
    Subject 0: (1*x)
    Subject 1: (tan(((x+x)/x))*x)
    Subject 2: (x*x)
    Subject 3: (x*(1+(sin(x)^(x/x))))
    Subject 4: (x*x)
    Subject 5: (x*x)
    Subject 6: (x*x)
    Subject 7: ((1+1)^x)
    Subject 8: (x*x)
    Subject 9: (x*(1/x))
    Subject 10: (x*(1/x))
    Subject 11: (x*(cos(tan(1))/x))
    Subject 12: 1
    Subject 13: x
    Subject 14: (x*x)
    Subject 15: (1*x)
    Subject 16: (x*x)
    Subject 17: (x*x)
    Subject 18: (x*x)
    Subject 19: (x*x)
    Subject 20: (x*1)
    Subject 21: (cos(sqrt(x))-x)
    Subject 22: (x*x)
    Subject 23: (1*x)
    Subject 24: (x*tan(x))
    Subject 25: (x*x)
    Subject 26: (1*x)
    Subject 27: (x*x)
    Subject 28: (x*x)
    Subject 29: (x*(1/x))
    Subject 30: (1*x)
    Subject 31: (1*x)
    Subject 32: 1
    Subject 33: (x*x)
    Subject 34: (x*x)
    Subject 35: (x*x)
    Subject 36: (x*x)
    Subject 37: x
    Subject 38: sin(ln(1))
    Subject 39: (x*x)
    Subject 40: (x*x)
    Subject 41: (x*x)
    Subject 42: (x*x)
    Subject 43: (x+(1/x))
    Subject 44: ((1-(x/(1^x)))*x)
    Subject 45: ln((1+(cos(x)^sin(1))))
    Subject 46: (x*x)
    Subject 47: (x*x)
    Subject 48: (x*x)
    Subject 49: (x*cos(x))
