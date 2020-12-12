#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("APDS9960센서 오류!");
    while (1);
  }
  //APDS.setSensitivity(80); //감도 조절 (1~100)
  Serial.println("제스처 인식 시작!");
}
void loop() {
  if (APDS.gestureAvailable()) {
    Serial.println("Gesture!");
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("윗쪽!");
        delay(100);
        break;
      case GESTURE_DOWN:
        Serial.println("아랫쪽!");
        delay(100);
        break;
      case GESTURE_LEFT:
        Serial.println("왼쪽!");
        delay(100);
        break;
      case GESTURE_RIGHT:
        Serial.println("오른쪽!");
        delay(100);
        break;
    }
  }
}
