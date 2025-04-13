#include <NewPing.h>
//#include <TinyGPS++.h>
//#include <SoftwareSerial.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//static const int RXPin = A5, TXPin = A4;
//static const uint32_t GPSBaud = 9600;
//TinyGPSPlus gps;
//SoftwareSerial ss(RXPin, TXPin);

int pin1 = A0;
int pin2 = A1;
int pin3 = A2;

int enA = 5;
int in1 = 4;
int in2 = 6;
int in3 = 7;
int in4 = 8;
int enB = 11;

void forward();
void backward();
void left();
void right();
void extremeleft();
void extremeright();
void stop();
void specialKey();

void setup(){
  Serial.begin(9600);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);


  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

//  ss.begin(GPSBaud);
}

void loop(){
//  delay(300);
  int x = digitalRead(pin1);
  int y = digitalRead(pin2);
  int z = digitalRead(pin3);
//  Serial.print("x: ");
//  Serial.print(x);
//  Serial.print(" , y: ");
//  Serial.print(y);
//  Serial.print(" , z: ");
//  Serial.println(z);

  unsigned int distance = sonar.ping_cm();
//  gps.encode(ss.read());
  
//  if (gps.location.isUpdated()){
//    String locationString = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
//    Serial.println(locationString);
//  }
  
  if (x==0 && y==0 && z==0 ){   // && distance>13
    Serial.println("forward");
    forward();
  }
  else if (x==0 && y==0 && z==1){
    Serial.println("backward");
    backward();
  }
  else if (x==0 && y==1 && z==0){  // && distance>13
    Serial.println("left");
    left();
  }
  else if (x==0 && y==1 && z==1){  // && distance>13
    Serial.println("right");
    right();
  }
  else if (x==1 && y==0 && z==1){
    Serial.println("extreme left");
    extremeright();
  }
  else if (x==1 && y==0 && z==0){
    Serial.println("extreme right");
    extremeleft();
  }
  else if (x==1 && y==1 && z==0){
    Serial.println("special Key");
    specialKey();
  }
  else{
    Serial.println("stop");
    stop();
  }
}

void forward(){
  analogWrite(enA, 160);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
  analogWrite(enB, 160);
}
void backward(){
  analogWrite(enA, 200);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);
}
void left(){
  analogWrite(enA, 190);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 90);
}
void right(){
  analogWrite(enA, 90);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 190);
}
void extremeleft(){
  analogWrite(enA, 120);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 120);
}
void extremeright(){
  analogWrite(enA, 120);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
  analogWrite(enB, 120);
}
void stop(){
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}
void specialKey(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
}
