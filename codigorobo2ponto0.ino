#include <AFMotor.h>

AF_DCMotor motorE(1);
AF_DCMotor motorD(2);

uint8_t velocidade = 150;

uint8_t TRIG = 40;
uint8_t ECHO = 38;

int duracao;
int distancia;
int distancia_min = 35;

void virarDireita(){
  motorE.setSpeed(velocidade);
  motorQ.setSpeed(velocidade);

  motorE.run(FORWARD);
  motorQ.run(BACKWARD);

  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);
}

void virarEsquerda(){
  motorE.setSpeed(velocidade);
  motorQ.setSpeed(velocidade);

  motorE.run(BACKWARD);
  motorQ.run(FORWARD);
  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);
}

void andaFrente(){
  motorE.setSpeed(velocidade);
  motorQ.setSpeed(velocidade);

  motorE.run(FORWARD);
  motorQ.run(FORWARD);
  delay(1000);

  motorE.run(RELEASE);
  motorD.run(RELEASE);
  delay(1000);
}

void setup() {
  pinMode(TRIG, OUTPUT);  
  pinMode(ECHO, INPUT);
}

void loop() {

  //Verifica a distância
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  duracao = pulseIn(ECHO, HIGH);
  distancia = duracao/58.2;

  if(distancia >= 0 && distancia <= distancia_min){
    viraDireita();
  }

  else{
    andaFrente();
  }
}
