//Barra sem pot em ATTiny85. Mensagem: Hackaton 2014. Usar ATTiny85 8MHz.
//Ilumina uma barra de LED's (B210SR)
//Utiliza um shift register (74HC595 ou 595). 
//Licenca: Apache 2.0 (use como quiser)
//http://www.apache.org/licenses/LICENSE-2.0.html
//Copyright 2014 Otavio Carneiro (carneiro.blog.br)

const int data_pin = 0; //DS (pino 14 no 595)    - ligado com um resistor de 300R
const int latch_pin = 1; //STCP (pino 12 no 595) - ligado com um resistor de 300R
const int save_pin = 2; //SHCP (pino 11 no 595)  - ligado com um resistor de 300R
//o pino 13 (OE - pause) foi ligado ao GND diretamente
//o pino 10 (MR - Nreset) foi ligado ao VCC com um resistor de 1k

const int led9 = 3;
const int led10 = 4;

//sequencia de valores a serem exibidos pela barra de leds, representados por 1 (aceso) e 0 (apagado)


int valores[] = {1023,32,32,32,1023,0, //H
400,592,592,480,512,0,//a
480,528,528,288,0,//c 
1022,64,176,768,0,//k
400,592,592,480,512,//a
8,8,1022,520,520,0,//t
448,544,544,448,0,//o
1008,32,32,960,0,0,//n
900,578,577,545,546,540,0,0,//2
508,514,514,514,508,0,0,//0
520,516,1023,512,512,0,//1
31,32,32,32,1023,0,0,0,0//4
                 };
//verifica quantos inteiros formam a mensagem
int qtde_valores = sizeof(valores) / sizeof(int); 

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop() {
  int micro_pausa = 420; //era 80. tentei 40, 20, 5, 1 com 1MHz
                       //com 8MHz - 2 fica coladinho, louco. 40 tb. 160 tb
                       // 8MHz e 380 comeca a ficar legal. anda devagar para a esquerda. em 400 tb
                       // 8MHz e 430 vai devagar para a direita
                       // 8MHz e 512 alterna entre Hacka e 2014 muito rapido. com 340 tb.
                       
                       
                       
  for(int saida = 0; saida <= qtde_valores; saida++) {
    acendeBarra(valores[saida]);
    //delay(pausa);
    delayMicroseconds(micro_pausa);
  }
}


//acende leds a partir de um inteiro que representa bits acesos ou apagados
void acendeBarra(int valor) {
    //utiliza o shift register para os 8 primeiros bits
    for(int pos_atual = 7; pos_atual >= 0; pos_atual--) {
      setData(bit_aceso(valor, pos_atual));
      save();
    }
    latch();
    digitalWrite(led9, bit_aceso(valor, 8));
    digitalWrite(led10, bit_aceso(valor, 9));
} 

//retorna verdadeiro se o bit na posicao "indice" for 1. 
boolean bit_aceso(int valor, int indice)
{
    return (valor & (1 << indice)) != 0;
}

//envia um valor no pino data
void setData(int value) {
  digitalWrite(data_pin, value);
}

//salva o dado no 595
void save() {
  digitalWrite(save_pin, HIGH);
  digitalWrite(save_pin, LOW);
}

//libera a exibicao dos dados gravados
void latch() {
  digitalWrite(latch_pin, HIGH);
  digitalWrite(latch_pin, LOW);
}
