#include <Bluepad32.h>
#include <math.h>

GamepadPtr myGamepad;

// Calibration values
const float pitchOffset = 76.0;  // when controller is level

// Normalize any angle to -180 to 180
float normalizeAngle(float angle) {
  if (angle > 180.0) angle -= 360.0;
  if (angle < -180.0) angle += 360.0;
  return angle;
}

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
  Serial.println("Ready. Waiting for controller...");
}

void loop() {
  BP32.update();

  if (myGamepad && myGamepad->isConnected()) {
    float ax = myGamepad->accelX();
    float ay = myGamepad->accelY();
    float az = myGamepad->accelZ();

    // Pitch calculation (now calibrated)
    float rawPitch = atan2(ay, az) * 180.0 / PI;
    float pitch = normalizeAngle(rawPitch - pitchOffset);

    // Roll calculation (already calibrated)
    float rawRoll = atan2(-ax, az) * 180.0 / PI;
    float roll = normalizeAngle(rawRoll + 180.0 - 360.0);

    // Print calibrated values
//    Serial.print("Pitch: ");
//    Serial.print(pitch, 2);
//    Serial.print("°, Roll: ");
//    Serial.print(roll, 2);
//    Serial.println("°");

    if (pitch < 21 && pitch > -21) {
      Serial.println("Stop");
    }
    else {
      if (roll < 16 && roll > -16) {
        Serial.println("Forward");
      }
      else if (roll >= 16 && roll < 54) {
        Serial.println("Left");
      }
      else if (roll >= 54 && roll <= 101) {
        Serial.println("Extreme Left");
      }
      else if (roll <= -16 && roll > -54) {
        Serial.println("Right");
      }
      else if (roll <= -54 && roll >= -101) {
        Serial.println("Extreme Right");
      }
    }
  }
  delay(50);
}
