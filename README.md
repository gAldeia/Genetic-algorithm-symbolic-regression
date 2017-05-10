# Genetic-algorithm-symbolic-regression

algoritmos desenvolvidos durante o aprendizado de programação genética e regressão simbólica.

## O projeto

A ideia principal do projeto era criar uma classe que gerenciasse uma população de árvores binárias. As árvores binárias formam expressões matemáticas, com operadores, variáveis e constantes.

### BinaryTree.hpp

Contém a implementação de todo o código. Consiste em duas classes:


node:

    É a estrutura fundamental da composição das árvores binárias.
    Contém todos os métodos necessários para trabalhar com as árvores binárias.
    

population:

    É uma classe que gerencia a população como um todo.
    Funciona como a criadora de eventos na população, invocando o crossover, mutação e outras 
    operações em cada um dos indivíduos.

### main.cpp

Aqui está definido o alvo da regressão simbólica, assim como os fatores necessários para a execução.

## Testes de execução

O exemplo a baixo é resultado da execução do algoritmo para os pontos (pontos alvo): 

    (0, 1), (1, 2), (2, 4), (3, 8), (4, 16), (5, 32), (6, 64)

O algoritmo basicamente tentará encontrar uma função que se aproxime dos pontos passados como alvo. Os pontos foram tirados da função f(x) = 2^x. No exemplo utilizado, o programa encontrou com êxito a função que deu origem aos pontos.

O resultado, usando uma população de 150 árvores, foi o seguinte:

    ACHOU: ((1+1)^x); na geração 21

    pop:
    individuo 0: (sin(x)^x)
    individuo 1: (sin(x)^x)
    individuo 2: x
    individuo 3: (sin(x)^x)
    individuo 4: (sin(x)^(x^cos(x)))
    individuo 5: (sin((1^1))^x)
    individuo 6: (sin(x)+x)
    individuo 7: (sin(x)^x)
    individuo 8: (sin(x)^x)
    individuo 9: (sin(x)^x)
    individuo 10: (((1+1)+1)^1)
    individuo 11: (sin(x)^x)
    individuo 12: (sin(x)^x)
    individuo 13: (sin(x)^x)
    individuo 14: (sin(x)^x)
    individuo 15: (x^x)
    individuo 16: (sin(x)^x)
    individuo 17: x
    individuo 18: 1
    individuo 19: (sin(x)^x)
    individuo 20: (sin(x)^x)
    individuo 21: 1
    individuo 22: x
    individuo 23: (sin(x)^x)
    individuo 24: ((((x/1)-1)^sin((x-1)))^cos(x))
    individuo 25: (x^x)
    individuo 26: (sin(x)^x)
    individuo 27: (sin(x)^1)
    individuo 28: (sin(x)^x)
    individuo 29: 1
    individuo 30: sin((x-x))
    individuo 31: (sin(x)^x)
    individuo 32: (sin(x)^(cos(1)-x))
    individuo 33: (sin(x)^x)
    individuo 34: (sin(x)^x)
    individuo 35: (sin(x)^x)
    individuo 36: (sin(x)^x)
    individuo 37: (sin(x)^1)
    individuo 38: cos(1)
    individuo 39: x
    individuo 40: (x^x)
    individuo 41: (sin(x)^x)
    individuo 42: (sin(x)^x)
    individuo 43: (sin(x)^x)
    individuo 44: (sin(x)^x)
    individuo 45: ((1-1)^x)
    individuo 46: (sin(x)^x)
    individuo 47: (sin(1)^x)
    individuo 48: (sin(x)-x)
    individuo 49: x
    individuo 50: (sin(x)^x)
    individuo 51: 1
    individuo 52: x
    individuo 53: 1
    individuo 54: (sin(x)^x)
    individuo 55: (sin((x+x))^x)
    individuo 56: (sin(x)^x)
    individuo 57: x
    individuo 58: (sin(x)^x)
    individuo 59: ((1+1)^x)
    individuo 60: (x^x)
    individuo 61: (sin(x)^x)
    individuo 62: ((((1-x)^(x+x))/((x+x)+x))^x)
    individuo 63: (x^x)
    individuo 64: (sin(x)^x)
    individuo 65: cos((1-(x/x)))
    individuo 66: (((x-(x+x))/x)^x)
    individuo 67: (sin(x)^1)
    individuo 68: (sin(x)^1)
    individuo 69: (sin(x)^x)
    individuo 70: (sin(x)^x)
    individuo 71: (sin(x)^x)
    individuo 72: (sin(1)^x)
    individuo 73: (sin(((1+1)*(1+1)))^x)
    individuo 74: (((1^(x*1))-x)/x)
    individuo 75: (sin(x)^x)
    individuo 76: 1
    individuo 77: x
    individuo 78: (1^((cos(x)+(1-x))+x))
    individuo 79: ((1^x)/((sin(x)*x)-1))
    individuo 80: 1
    individuo 81: sin((1-x))
    individuo 82: (1*x)
    individuo 83: 1
    individuo 84: (1^x)
    individuo 85: x
    individuo 86: (1/(x+1))
    individuo 87: cos(1)
    individuo 88: ((((1^x)+x)+(x^(1+x)))/sin(x))
    individuo 89: (x*cos(1))
    individuo 90: 1
    individuo 91: x
    individuo 92: ((((1/1)+(1*x))^cos(1))^sin((1+x)))
    individuo 93: ((1+(x/sin(x)))/sin(((x+1)+x)))
    individuo 94: 1
    individuo 95: (1+1)
    individuo 96: 1
    individuo 97: ((sin(1)*x)*(x-((1*x)^(x*1))))
    individuo 98: 1
    individuo 99: 1
    individuo 100: 1
    individuo 101: (x/cos(cos(cos(1))))
    individuo 102: x
    individuo 103: (1+sin(cos(1)))
    individuo 104: (((x-(1-1))^1)/(cos(sin(1))^1))
    individuo 105: cos(cos((x/(1/1))))
    individuo 106: 1
    individuo 107: ((x+((1-x)+x))*cos((cos(x)/(x-1))))
    individuo 108: 1
    individuo 109: 1
    individuo 110: x
    individuo 111: 1
    individuo 112: (x-(1*((1/x)*sin(x))))
    individuo 113: sin((x^cos(x)))
    individuo 114: x
    individuo 115: (1*x)
    individuo 116: x
    individuo 117: (1-x)
    individuo 118: cos(1)
    individuo 119: 1
    individuo 120: 1
    individuo 121: (x-1)
    individuo 122: ((1^x)-(x/sin(1)))
    individuo 123: x
    individuo 124: 1
    individuo 125: 1
    individuo 126: x
    individuo 127: x
    individuo 128: (1-1)
    individuo 129: 1
    individuo 130: cos(1)
    individuo 131: x
    individuo 132: cos(cos(1))
    individuo 133: cos(1)
    individuo 134: (sin(x)^(((1^x)+sin(1))^(1-(1-x))))
    individuo 135: 1
    individuo 136: sin(1)
    individuo 137: sin(x)
    individuo 138: (x^x)
    individuo 139: (x^x)
    individuo 140: (sin(x)+1)
    individuo 141: sin(x)
    individuo 142: x
    individuo 143: 1
    individuo 144: (1*x)
    individuo 145: (x^cos((x*(x-1))))
    individuo 146: ((sin(x)/1)^x)
    individuo 147: ((sin((x+x))+1)/x)
    individuo 148: (1-1)
    individuo 149: cos(1)
