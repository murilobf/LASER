#include <AFMotor.h>

AF_DCMotor motorE(1);
AF_DCMotor motorD(2);

uint8_t velocidade = 150;

uint8_t TRIG = 40;
uint8_t ECHO = 38;

int duracao;
int distancia;
int distancia_min = 35;

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

  int dist = sonar();

  //Vira pra direita novamente se necessário
  if(dist >= 0 && dist <= distancia_min){
    viraDireita();
  }

  //Anda um pouco pra ser possível desviar do obstáculo
  andaFrente();

  //Volta pra direção original
  viraEsquerda();
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

void setup() {
  pinMode(TRIG, OUTPUT);  
  pinMode(ECHO, INPUT);
}

//Essa variação do código original tenta sempre seguir pelo mesmo caminho,
//virando pra direita pra desviar de obstáculos mas voltando pra direção original se possível
void loop() {

  //Verifica a distância
  distancia = sonar();

  //Tenta contornar o obstáculo (se não for possível, como é o caso de quando atinge a parede, ele começa a dar a volta) 
  if(distancia >= 0 && distancia <= distancia_min){
    viraDireita();
  }

  else{
    andaFrente();
  }
}
