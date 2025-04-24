#include <AFMotor.h>

AF_DCMotor motorE(1);
AF_DCMotor motorD(2);

uint8_t velocidade = 150;

uint8_t TRIG = 40;
uint8_t ECHO = 38;

uint8_t pinoSensor1 = 19;
uint8_t pinoSensor2 = 20;

int duracao;
int distancia;
int distancia_min = 35;

unsigned int pulsos1;
unsigned int pulsos2;
volatile double timeold;

//Funções executadas a cada interrupção
void contador1(){
  pulsos1++;
}

void contador2(){
  pulsos2;
}

//Iguala a velocidade dos motores
void igualaVel(){
  if(millis() - timeold >= 1){
    if(pulsos1 < pulsos2){
      detachInterrupt(3);

      //Iguala os motores
      while(pulsos1 < pulsos2){
        motorD.run(RELEASE);
        motorE.setSpeed(velocidade);
        motorE.run(FORWARD);
      }

      attachInterrupt(3, contador2, FALLING);
    }

    else if(pulsos1 > pulsos2){
      detachInterrupt(4);

      //Iguala os motores
      while(pulsos1 > pulsos2){
        motorE.run(RELEASE);
        motorD.setSpeed(velocidade);
        motorD.run(FORWARD);
      }

      attachInterrupt(4, contador1, FALLING);
    }

    else{
      pulsos1 = 0;
      pulsos2 = 0;
    }

    timeold = millis();
  }
}

//Função do sensor ultrassonico
int sonar(){
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);

  int dur = pulseIn(ECHO, HIGH);
  int dist = dur/58.2;

  return dist;
}

//Funções de movimentação 
void viraEsquerda(){
  motorE.setSpeed(velocidade);
  motorD.setSpeed(velocidade);

  motorE.run(BACKWARD);
  motorD.run(FORWARD);
  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);
}

void viraDireita(){
  motorE.setSpeed(velocidade);
  motorD.setSpeed(velocidade);

  motorE.run(FORWARD);
  motorD.run(BACKWARD);

  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);

  //O código abaixo é responsável por fazer ele voltar pra direção original, se possível

  rotina();
}

void andaFrente(){
  motorE.setSpeed(velocidade);
  motorD.setSpeed(velocidade);

  motorE.run(FORWARD);
  motorD.run(FORWARD);
  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);
}

//A rotina a ser chamada no loop, está separado ao invés de no loop principal pois também é usada na função de virar à direita
void rotina(){
  //Verifica a distância
  distancia = sonar();

  //Tenta contornar o obstáculo (se não for possível, como é o caso de quando atinge a parede, ele começa a dar a volta) 
  if(distancia >= 0 && distancia <= distancia_min){
    viraDireita();
  }

  andaFrente();
}

void setup() {
  pinMode(TRIG, OUTPUT);  
  pinMode(ECHO, INPUT);
  pinMode(pinoSensor1, INPUT);
  pinMode(pinoSensor2, INPUT);
  
  attachInterrupt(4, contador1, FALLING);
  attachInterrupt(3, contador2, FALLING);

  pulsos1 = 0;
  pulsos2 = 0;

  timeold = millis();
}

//Essa variação do código original tenta sempre seguir pelo mesmo caminho,
//virando pra direita pra desviar de obstáculos mas voltando pra direção original se possível
void loop() {
  igualaVel();
  rotina();
}
