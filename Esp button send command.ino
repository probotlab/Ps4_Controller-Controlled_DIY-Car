#include <Bluepad32.h>

GamepadPtr myGamepad;

int pin1 = 12;  // connects to A1
int pin2 = 13; // connects to A2
int pin3 = 15; // connects to A3
const int led_builtin = 4;

void onConnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad connected");
  myGamepad = gp;
}

void onDisconnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad disconnected");
  if (gp == myGamepad) {
    myGamepad = nullptr;
  }
}

void setup() {
  Serial.begin(115200);
  BP32.forgetBluetoothKeys();
  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
  
//  pinMode(LED_PIN, OUTPUT);
//  digitalWrite(LED_PIN, LOW);
    pinMode(pin3, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(led_builtin, OUTPUT);

    digitalWrite(pin1, HIGH);  
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(led_builtin, LOW);

  Serial.println("Ready. Waiting for controller...");
}

void loop() {
  BP32.update();

  if (myGamepad && myGamepad->isConnected()) {
    uint16_t dpad = myGamepad->dpad();
    uint16_t buttons = myGamepad->buttons();
    
    if (dpad == 0x01) {
      Serial.println("D-Pad UP -> LED");
      digitalWrite(led_builtin, HIGH);
    }
    
    if (dpad == 0x02) {
      Serial.println("D-Pad DOWN -> Special Key");
      digitalWrite(pin1, HIGH);  
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
    }
    
    if (dpad == 0x04) {
      Serial.println("D-Pad Right -> Right");
      digitalWrite(pin1, LOW);  
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
    }
    
    if (dpad == 0x08) {
      Serial.println("D-Pad Left -> Left");
      digitalWrite(pin1, LOW);  
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
    }

    if (buttons & 0x0010) {  
      Serial.println("Button L1 -> Extreme Left");
      digitalWrite(pin1, HIGH);  
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
    }
    
    if (buttons & 0x0020) {   
      Serial.println("Button R1 -> Extreme Right");
      digitalWrite(pin1, HIGH);  
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
    }
    
    if (buttons & 0x0040) { 
      Serial.println("Button L2 -> Backward");
      digitalWrite(pin1, LOW);  
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
    }
    
    if (buttons & 0x0080) {  
      Serial.println("Button R2 -> Forward");
      digitalWrite(pin1, LOW);  
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
    }
    
    if (!(dpad == 0x01 || dpad == 0x02 || dpad == 0x04 || dpad == 0x08 ||
          (buttons & 0x0010) || (buttons & 0x0020) ||
          (buttons & 0x0040) || (buttons & 0x0080))) {
      Serial.println("Stop");
      digitalWrite(pin1, HIGH);  
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(led_builtin, LOW);
    }
  }
  delay(10);
}
