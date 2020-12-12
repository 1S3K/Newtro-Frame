#include <Arduino_APDS9960.h>

#define PIXEL 0
#define EQUALIZER 1
#define EMOTION 2
#define HEART 3

#define ANDROID 10
#define TREE 11
#define RAINBOW 12
#define SNOW 13

// 프로그램 전반
int prevMenu(int menu);
int nextMenu(int menu);
void switchMenu(int menu);

// 메뉴0 : 픽셀모드
void pixelMode(int pixel);
void showAndroid();
void showTree();
void showRainbow();
void showSnow();
int prevPixel(int pixel);
int nextPixel(int pixel);

// 메뉴1 : 이퀄라이저모드
void equalizerMode();

// 메뉴2 : 감정모드
void emotionMode();

// 메뉴3 : 심박모드
void heartMode();


int menu = 0;
int pixel = 10;

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
    int gesture = APDS.readGesture();
    // XXX : if gesture up/down 고려할 필요 없는가?
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("위로!");
        menu=prevMenu(menu);
        switchMenu(menu);
        break;
      case GESTURE_DOWN:
        Serial.println("아래로!");
        menu=nextMenu(menu);
        switchMenu(menu);
        break;
      case GESTURE_LEFT:
        Serial.println("왼쪽으로!");
        if(menu == PIXEL){
          pixel=prevPixel(pixel);
          pixelMode(pixel);
        }
        break;
      case GESTURE_RIGHT:
        Serial.println("오른쪽으로!");
        if(menu == PIXEL){
          pixel=nextPixel(pixel);
          pixelMode(pixel);
        }
        break;
    }
  }
}

void switchMenu(int menu){
  if(menu==PIXEL) pixelMode(pixel);
  else if(menu == EQUALIZER) equalizerMode();
  else if(menu == EMOTION) emotionMode();
  else if(menu == HEART) heartMode();
}

int prevMenu(int menu){
  if(menu == 0) return 3;
  return menu-1;
}

int nextMenu(int menu){
  if(menu == 3) return 0;
  return menu+1;
}

void switchPixel(int pixel){
  if(pixel==PIXEL) pixelMode(pixel);
  else if(pixel == EQUALIZER) equalizerMode();
  else if(pixel == EMOTION) emotionMode();
  else if(pixel == HEART) heartMode();
}

int prevPixel(int pixel){
  if(pixel == 10) return 13;
  return pixel-1;
}

int nextPixel(int pixel){
  if(pixel == 13) return 10;
  return pixel+1;
}

void pixelMode(int pixel){
  Serial.println("0. 픽셀모드");
  switch (pixel) {
    case ANDROID:
      showAndroid();
      break;
    case TREE:
      showTree();
      break;
    case RAINBOW:
      showRainbow();
      break;
    case SNOW:
      showSnow();
      break;
  }
}

void showAndroid(){
  Serial.println("10.Android");
}
void showTree(){
  Serial.println("11.tree");
}
void showRainbow(){
  Serial.println("12.rainbow");
}
void showSnow(){
  Serial.println("13.snow");
}

void equalizerMode(){
  Serial.println("1.이퀄라이저");
}
void emotionMode(){
  Serial.println("2.이모션");
}
void heartMode(){
  Serial.println("3.하트");
}