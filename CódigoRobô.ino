#define ENA 3 // Azul
#define IN1 5 // Roxo 
#define IN2 4 // Amarelo
#define IN3 7 // Laranja
#define IN4 6 // Cinza
#define ENB 9 // Verde
#define pino_trigger 11 // Verde
#define pino_echo 12 // Azul
#define sensorEsq A2 // Sensor Esquerdo Cinza
#define sensorDir A3 // Sensor Direito Branco
#define sensorCen A1 // Sensor Centro Branco

#define velocidade 75 // Velocidade Constante
#define correcaoMotor 30 // Correção

int velA;
int velB;
int parar = 0;
int obs = 20;
int faixa = 1;
int Nfaixa = 0;

#include <Ultrasonic.h>
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup() {
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);
  Serial.begin(9600);
  pinMode(sensorEsq, INPUT);
  pinMode(sensorDir, INPUT);
  pinMode(sensorCen, INPUT);

  delay(100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void loop() {

  
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  int valorSensorEsq = digitalRead( sensorEsq);
  int valorSensorDir = digitalRead( sensorDir);
  int valorSensorCen = digitalRead( sensorCen);
  
  if (cmMsec <= obs) {
    velA = parar; velB = parar;
    Serial.print(cmMsec);
    Serial.print("\n");
  } else if ((valorSensorEsq == faixa) || ((valorSensorEsq == faixa && (valorSensorCen == faixa)))) {
    velA = correcaoMotor;
    velB = velocidade;
    Serial.print("ESQUERDO");
    Serial.print("\n");
  } else if (valorSensorDir == faixa || ((valorSensorDir == faixa) && (valorSensorCen == faixa))) {
    velA = velocidade;
    velB = correcaoMotor;
    Serial.print("DIREITO");
    Serial.print("\n");
  } else if ((valorSensorCen == faixa) || ((valorSensorEsq == faixa) && (valorSensorDir == faixa) && (valorSensorCen == faixa))) {
    velA = velocidade;
    velB = velocidade;
    Serial.print("CENTRAL");
    Serial.print("\n");
  } else if ((valorSensorEsq == Nfaixa) && (valorSensorDir == Nfaixa) && (valorSensorCen == Nfaixa)) {
    velA = parar;
    velB = parar;
    Serial.print("NENHUM");
    Serial.print("\n");
  }
  Serial.print(valorSensorEsq);
  Serial.print("      ||      ");
  Serial.print(valorSensorCen);
  Serial.print("      ||      ");
  Serial.print(valorSensorDir);
  Serial.print("\n");
  analogWrite(ENB, velB);
  analogWrite(ENA, velA);
}
