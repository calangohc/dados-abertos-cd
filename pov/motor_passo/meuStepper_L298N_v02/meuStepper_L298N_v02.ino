//Controlador de motor de passo
//Autor: Otavio Carneiro dos Santos
//Licenca: MIT (faca o que quiser!)
//v2.1 = comentarios para conexao ao L298N
//v2.0 = pausas em microssegundos
//v1.1 = dois LED's para debug: um para cada direcao
//v1.0 = Explicitamente manda sinal LOW para todos os polos quando deve ficar parado
//v0.8 = Controla a direcao e velocidade a partir da leitura do potenciometro
//v0.7 = Controle de velocidade de acordo com a leitura do potenciometro
//v0.6 = Contem algoritmo para leitura do potenciometro e 
//        //exibicao em um led para debug

//pino 1 do L298N (curr sens A) se conecta ao GRN com um resistor de 2R
//pino 2 do L298N (output 1) se conecta ao pino 1 do motor de passo
//pino 3 do L298N (output 2) se conecta ao pino 2 do motor de passo
//pino 4 do L298N (supply voltage) se conecta a uma fonte de energia de maior potencia
//                 a corrente neste pino alimentarah o motor de passo
const int sinal1 = 8;  //pino 5 do L298N (input1)
//pino 6 do L298N (enable A) se conecta aos 5V do Arduino
const int sinal2 = 9;  //pino 7 do L298N (input2)
//pino 8 do L298N (GND) se conecta ao GND do Arduino
//pino 9 do L298N (logic supply voltage) se conecta aos 5V do Arduino
const int sinal3 = 10; //pino 10 do L298N (input3)
//pino 11 do L298N (enable B) se conecta aos 5V do Arduino
const int sinal4 = 11; //pino 12 do L298N (input4)
//pino 13 do L298N (output 3) se conecta ao pino 3 do motor de passo
//pino 14 do L298N (output 4) se conecta ao pino 4 do motor de passo
//pino 15 do L298N (curr sens B) se conecta ao GRN com um resistor de 2R

const int potenciometro = A0; //pino de entrada analogica
const int ledDebugIda = 5; //pino PWM com um resistor de 300R e um LED vermelho
const int ledDebugVolta = 6; //LED verde
const int buzzer = 3; ////pino PWM com um resistor de 300R e um piezo buzzer

//minimo e maximo para pausa em microssegundos (1 milionesimo de seg)
const int MIN_MICRO_PAUSA = 300;
const int MAX_MICRO_PAUSA = 20000;

const boolean DEBUG = false;

//delay entre os sinais
int pausa = MAX_MICRO_PAUSA;

int valorPot = 0;
int valorDebug = 0;

void setup() {
  pinMode(sinal1, OUTPUT);
  pinMode(sinal2, OUTPUT);
  pinMode(sinal3, OUTPUT);
  pinMode(sinal4, OUTPUT);
  
  if(DEBUG) {
    pinMode(ledDebugIda, OUTPUT);
    pinMode(ledDebugVolta, OUTPUT); 
    pinMode(buzzer, OUTPUT); 
  }
}

void loop() {
  valorPot = analogRead(potenciometro);
  //se o potenciometro estiver abaixo da metade, vai para frente
  if (valorPot < 500) {
    if (DEBUG) {
      valorDebug = map(valorPot,0,499,255,0);
      analogWrite(ledDebugIda,valorDebug); 
      analogWrite(ledDebugVolta,LOW); 
    } else {
      //em modo debug, a pausa eh fixa
      pausa = map(valorPot,0,499,MIN_MICRO_PAUSA,MAX_MICRO_PAUSA);
    }
     frente(); //4-2-3-1
  //se estiver acima da metade, vai para tras
  } else if (valorPot > 524) {
    if (DEBUG) {
      valorDebug = map(valorPot,525,1023,0,255);
      analogWrite(ledDebugIda,LOW); 
      analogWrite(ledDebugVolta,valorDebug); 
    } else {
      pausa = map(valorPot,525,1023,MAX_MICRO_PAUSA,MIN_MICRO_PAUSA);
    }
    tras();  //1-3-2-4
  //no meio, ha uma faixa de leituras em que o motor fica parado
  } else {
    if (DEBUG) {
      analogWrite(ledDebugIda,LOW); 
      analogWrite(ledDebugVolta,LOW); 
    }
    parar();
  }
}
//1-3-2-4 - vermelho
void frente() {
  enviaSinal1();  //sinal1: +-oo
  enviaSinal3();  //sinal3: oo+-
  enviaSinal2();  //sinal2: -+oo  
  enviaSinal4();  //sinal4: oo-+
}

//4-2-3-1 - verde
void tras() {
  //4231 - volta um, vai um
  //231 - idem, volta um, vai um
  //3231 - volta, vai, vai, volta
  //4241 - nada
  enviaSinal4();  //sinal4: oo-+
  if (DEBUG) {
    tone(buzzer, 500, 100);
  }
  enviaSinal2();  //sinal2: -+oo  
  enviaSinal3();  //sinal3: oo+-
  enviaSinal1();  //sinal1: +-oo
  if (DEBUG) {
    tone(buzzer, 100, 50);
  }
}

void enviaSinal1() {
  //sinal1: +-oo
  digitalWrite(sinal2, LOW);
  digitalWrite(sinal3, LOW);
  digitalWrite(sinal4, LOW);  
  digitalWrite(sinal1, HIGH);
  delayMicroseconds(pausa);
}

void enviaSinal2() {
  //sinal2: -+oo
  digitalWrite(sinal1, LOW);
  digitalWrite(sinal3, LOW);
  digitalWrite(sinal4, LOW);  
  digitalWrite(sinal2, HIGH);
  delayMicroseconds(pausa);
}

void enviaSinal3() {
  //sinal3: oo+-
  digitalWrite(sinal1, LOW);
  digitalWrite(sinal2, LOW);
  digitalWrite(sinal4, LOW);  
  digitalWrite(sinal3, HIGH);
  delayMicroseconds(pausa);
}

void enviaSinal4() {
  //sinal4: oo-+
  digitalWrite(sinal1, LOW);
  digitalWrite(sinal2, LOW);
  digitalWrite(sinal3, LOW);
  digitalWrite(sinal4, HIGH);  
  delayMicroseconds(pausa);
}

//envia LOW para todos os sinais
void parar() {
  digitalWrite(sinal1, LOW);
  digitalWrite(sinal2, LOW);
  digitalWrite(sinal3, LOW);
  digitalWrite(sinal4, LOW);  
}
