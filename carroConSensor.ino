#include <Servo.h>
#include <NewPing.h>

// Definición de pines para el control de motores
const int MotorIzquierdoAdelante = 7;
const int MotorIzquierdoAtras = 6;
const int MotorDerechoAdelante = 5;
const int MotorDerechoAtras = 4;

// Definición de pines para el sensor ultrasónico
#define pin_trig A1
#define pin_echo A2
#define distancia_maxima 200

boolean avanza = false; // Variable para controlar la dirección del movimiento
int distancia = 100; // Distancia inicial

NewPing sonar(pin_trig, pin_echo, distancia_maxima);
Servo motor_servo;

void setup() {
  // Configuración de pines de salida para el control de motores
  pinMode(MotorDerechoAdelante, OUTPUT);
  pinMode(MotorIzquierdoAdelante, OUTPUT);
  pinMode(MotorIzquierdoAtras, OUTPUT);
  pinMode(MotorDerechoAtras, OUTPUT);

  // Inicialización del servo motor
  motor_servo.attach(10);

  // Posicionamiento inicial del servo y lectura de distancia
  motor_servo.write(115);
  for (int i = 0; i < 4; ++i) {
    delay(2000);
    distancia = leerDistancia();
    delay(100);
  }
}

void loop() {
  delay(50);
  distancia = leerDistancia();

  if (distancia <= 45) {
    detenerMovimiento();
    delay(200);
    retroceder();
    delay(400);
    detenerMovimiento();
    delay(200);
    int distanciaDerecha = mirarDerecha();
    delay(200);
    int distanciaIzquierda = mirarIzquierda();
    delay(200);

    // Gira hacia la dirección con mayor espacio libre
    if (distancia >= distanciaIzquierda) {
      girarDerecha();
      detenerMovimiento();
    } else {
      girarIzquierda();
      detenerMovimiento();
    }
  } else {
    avanzar();
  }
}

// Gira el servo a la derecha y devuelve la distancia actual
int mirarDerecha() {
  motor_servo.write(50);
  delay(500);
  int distancia = leerDistancia();
  delay(100);
  motor_servo.write(115);
  return distancia;
}

// Gira el servo a la izquierda y devuelve la distancia actual
int mirarIzquierda() {
  motor_servo.write(170);
  delay(500);
  int distancia = leerDistancia();
  delay(100);
  motor_servo.write(115);
  return distancia;
}

// Lee la distancia actual desde el sensor ultrasónico
int leerDistancia() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250; // Valor de distancia máximo en caso de error
  }
  return cm;
}

// Detiene todos los motores
void detenerMovimiento() {
  digitalWrite(MotorDerechoAdelante, LOW);
  digitalWrite(MotorIzquierdoAdelante, LOW);
  digitalWrite(MotorDerechoAtras, LOW);
  digitalWrite(MotorIzquierdoAtras, LOW);
}

// Mueve hacia adelante
void avanzar() {
  if (!avanza) {
    avanza = true;
    digitalWrite(MotorIzquierdoAdelante, HIGH);
    digitalWrite(MotorDerechoAdelante, HIGH);
    digitalWrite(MotorIzquierdoAtras, LOW);
    digitalWrite(MotorDerechoAtras, LOW);
  }
}

// Mueve hacia atrás
void retroceder() {
  avanza = false;
  digitalWrite(MotorIzquierdoAtras, HIGH);
  digitalWrite(MotorDerechoAtras, HIGH);
  digitalWrite(MotorIzquierdoAdelante, LOW);
  digitalWrite(MotorDerechoAdelante, LOW);
}

// Gira a la derecha
void girarDerecha() {
  digitalWrite(MotorIzquierdoAdelante, HIGH);
  digitalWrite(MotorDerechoAtras, HIGH);
  digitalWrite(MotorIzquierdoAtras, LOW);
  digitalWrite(MotorDerechoAdelante, LOW);
  delay(400);
  digitalWrite(MotorIzquierdoAdelante, HIGH);
  digitalWrite(MotorDerechoAdelante, HIGH);
  digitalWrite(MotorIzquierdoAtras, LOW);
  digitalWrite(MotorDerechoAtras, LOW);
}

// Gira a la izquierda
void girarIzquierda() {
  digitalWrite(MotorIzquierdoAtras, HIGH);
  digitalWrite(MotorDerechoAdelante, HIGH);
  digitalWrite(MotorIzquierdoAdelante, LOW);
  digitalWrite(MotorDerechoAtras, LOW);
  delay(400);
  digitalWrite(MotorIzquierdoAdelante, HIGH);
  digitalWrite(MotorDerechoAdelante, HIGH);
  digitalWrite(MotorIzquierdoAtras, LOW);
  digitalWrite(MotorDerechoAtras, LOW);
}

