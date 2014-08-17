dados-abertos-cd/pov
================

Projeto para criação de um display que utilize o princípio da persistência retiniana (ou persistência de visão ou POV da sigla em inglês, persistence of vision).

O Projeto faz parte da iniciativa Arduino para a Cidadania do Laboratório Hacker da Câmara dos Deputados do Brasil.

O display POV é composto por duas partes: um controlador de motor de passo e uma barra de LED's.

O controlador de motor de passo é baseado em um chip L298N. As quatro saídas deste chip são conectados às quatro entradas do motor de passo bipolar utilizado no projeto. O motor de passo foi reaproveitado de sucata, não se sabe a origem nem suas especificações. A experiência mostra, no entanto, que ele funciona razoavelmente bem com uma alimentação de 5V. Um Arduino Uno R3 é utilizado para mandar sinais para o chip L298N. Um potenciômetro é utilizado para o ajuste da velocidade do motor.

A barra de LED's é do tipo B210SR. Ela possui 10 LED's e é controlada por um shift register do tipo 74HC595, conectado a uma ATTiny85, que faz as vezes de controlador. O texto (ou desenho) apresentado pelo display é definido diretamente no sketch (programa) que roda na ATTiny. A sequência de bits que representa LED's acesos e apagados é desenhada em uma planilha do tipo LibreOffice Calc, que converte os valores binários para decimais, listados dentro do programa.

