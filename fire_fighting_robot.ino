#include <Servo.h> // Include the Servo library

Servo myservo;

int pos = 0;
boolean fire = false;

#define Left 9 // Left flame sensor
#define Right 10 // Right flame sensor
#define Forward 8 // Front flame sensor
#define LM1 2 // Left motor pin 1
#define LM2 3 // Left motor pin 2
#define RM1 4 // Right motor pin 1
#define RM2 5 // Right motor pin 2
#define pump 6 // Pump control pin

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(11); // Attach servo to pin 11
  myservo.write(90); // Initial servo position
}

void put_off_fire() {
  delay(500);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  digitalWrite(pump, HIGH);
  delay(500);
  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  digitalWrite(pump, LOW);
  myservo.write(90);
  fire = false;
}

void loop() {
  myservo.write(90); // Sweep servo

  if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  } else if (digitalRead(Forward) == 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
  } else if (digitalRead(Left) == 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  } else if (digitalRead(Right) == 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }

  delay(300); // Adjust distance sensitivity

  while (fire == true) {
    put_off_fire();
  }
}
