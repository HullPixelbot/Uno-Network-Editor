#include <Arduino.h>
#include "RobotWebServer.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Server starting");
  setupServer();
}

void loop() {
  updateServer();
}
 