#include <Arduino_APDS9960.h>
#include <PDM.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL 0
#define EQUALIZER 1
#define EMOTION 2
#define HEART 3

#define ANDROID 10
#define TREE 11
#define RAINBOW 12
#define SNOW 13

#define PIN 6
#define NUMPIXELS 256
#define BRIGHTNESS 5
#define SENSITIVITY 400
#define DELAY 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// 0~15, 31~16, 32~47, 63~48
int pixelMap[16][16];
int C[16][3] = {
  0,0,120, 0,40,120, 0,80,120, 0,120,120, 
  0,120,0, 40,120,0, 80,120,0, 120,120,0,
  120,0,0, 120,0,40, 120,0,80, 120,0,120,
  120,120,120, 60,120,120, 120,60,120, 120,120,60};

int C2[16][3] = {
   120,120,60, 120,60,120, 60,120,120,120,120,120,
   120,0,120,120,0,80, 120,0,40, 120,0,0, 
   120,120,0,80,120,0,40,120,0,  0,120,0, 
   0,120,120,  0,80,120,  0,40,120,0,0,120
};
//int C[16][3] = {0, 0, 50,0, 0, 50,0, 0, 50,0, 0, 50,0, 50, 0,0, 50, 0,0, 50, 0,0, 50, 0,50,0,0,50,0,0,50,0,0,50,0,0,50,50,50,50,50,50,50,50,50,50,50,50}; //높이별 색상 지정 (파 초 빨 흰)
//int C[16][3] = {0, 0, 50, 0, 50, 0, 50, 0, 0, 50, 50, 50,0, 0, 50, 0, 50, 0, 50, 0, 0, 50, 50, 50,0, 0, 50, 0, 50, 0, 50, 0, 0, 50, 50, 50,0, 0, 50, 0, 50, 0, 50, 0, 0, 50, 50, 50}; //높이별 색상 지정 (파 초 빨 흰)
int VUlevelMap[16] = {0};

// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256];

// number of samples read
volatile int samplesRead;

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
  for (int i = 0; i < 16; i++){ // 소리경계 설정
    VUlevelMap[i] = SENSITIVITY * i;
    for(int j=0;j<16;j++){
      if(i%2 == 1) pixelMap[i][j] = i*16 + j; // 정방향
      else pixelMap[i][j] = (i+1)*16 -j; // 역방향
    }
  }
  Serial.begin(9600);
  while (!Serial);

  // configure the data receive callback
  PDM.onReceive(onPDMdata);

  // optionally set the gain, defaults to 20
  // PDM.setGain(30);

  // initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  do {
    // wait for samples to be read
    int v[16] = {0};
    if (samplesRead) {
      // print samples to the serial monitor or plotter
      for(int i=0;i<samplesRead;i++){
        int bar = i/16;
        v[bar] += abs(sampleBuffer[i]);
      }
      
      // clear the read count
      samplesRead = 0;
    }
    Serial.print("현재 음량 : ");
    for(int i=0;i<16;i++){
      Serial.print(v[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
  
    for(int i=0;i<16;i++){ // i는 막대요
      for(int j=0;j<16;j++){ // j는 층이로다
        if(v[i] > VUlevelMap[j] && i%2 == 1) pixels.setPixelColor(pixelMap[i][j], pixels.Color(C[i][0], C[i][1], C[i][2])); // i인지 j인지 둘중하나.
        else if(v[i] > VUlevelMap[j] && i%2 ==0 ) pixels.setPixelColor(pixelMap[i][j], pixels.Color(C2[i][0], C2[i][1], C2[i][2])); // i인지 j인지 둘중하나.
        else pixels.setPixelColor(pixelMap[i][j], pixels.Color(0,0,0));
      }
    }
    pixels.show();
    
    delay(DELAY);
    if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    
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
      }
    }
  } while(menu==EQUALIZER);
  
}
void emotionMode(){
  Serial.println("2.이모션");
}
void heartMode(){
  Serial.println("3.하트");
}
void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}