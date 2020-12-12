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
void showAndroid(uint8_t faceR, uint8_t faceG, uint8_t faceB);
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
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  switch (pixel) {
    case ANDROID:
      showAndroid(0, 255, 0);
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

void showAndroid(uint8_t faceR, uint8_t faceG, uint8_t faceB) {
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  int arm_mode = 0;
  // ear
  pixels.setPixelColor(3,faceR,faceG,faceB);
  pixels.setPixelColor(12,faceR,faceG,faceB);
  pixels.setPixelColor(27,faceR,faceG,faceB);
  pixels.setPixelColor(20,faceR,faceG,faceB);

  // head 
  for (int i=37 ; i<43 ; i++) // line1
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=52 ; i<60 ; i++) // line2
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=68 ; i<76 ; i++) // line3
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=84 ; i<92 ; i++) // line4
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  // eye
  pixels.setPixelColor(54,255,255,255);
  pixels.setPixelColor(57,255,255,255);
  

  

  // body
  for (int i=116 ; i<124 ; i++) // line1
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=132 ; i<140 ; i++) // line2
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=148 ; i<156 ; i++) // line3
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=164 ; i<172 ; i++) // line4
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=180 ; i<188 ; i++) // line4
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=196 ; i<204 ; i++) // line4
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }
  for (int i=213 ; i<219 ; i++) // line4
  {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }


  // legs
  pixels.setPixelColor(230,faceR,faceG,faceB);
  pixels.setPixelColor(249,faceR,faceG,faceB);
  pixels.setPixelColor(233,faceR,faceG,faceB);
  pixels.setPixelColor(246,faceR,faceG,faceB);

  do{
    if(arm_mode == 1) {
      pixels.setPixelColor(114, 0,0,0);
      pixels.setPixelColor(142, 0,0,0);
      pixels.setPixelColor(144, 0,0,0);
      pixels.setPixelColor(125, 0,0,0);
      pixels.setPixelColor(129, 0,0,0);
      pixels.setPixelColor(159, 0,0,0);  
      // left-arm
      pixels.setPixelColor(125,faceR,faceG,faceB);
      pixels.setPixelColor(130,faceR,faceG,faceB);
      pixels.setPixelColor(157,faceR,faceG,faceB);
      pixels.setPixelColor(162,faceR,faceG,faceB);
    
      // right-arm
      pixels.setPixelColor(114,faceR,faceG,faceB);
      pixels.setPixelColor(141,faceR,faceG,faceB);
      pixels.setPixelColor(146,faceR,faceG,faceB);
      pixels.setPixelColor(173,faceR,faceG,faceB);
    }
  
    else if(arm_mode == 2) {
      pixels.setPixelColor(125,0,0,0);
      pixels.setPixelColor(130,0,0,0);
      pixels.setPixelColor(157,0,0,0);
      pixels.setPixelColor(162,0,0,0);
      pixels.setPixelColor(114,0,0,0);
      pixels.setPixelColor(141,0,0,0);
      pixels.setPixelColor(146,0,0,0);
      pixels.setPixelColor(173,0,0,0);
      pixels.setPixelColor(114, 0,255,0);
      pixels.setPixelColor(142, 0,255,0);
      pixels.setPixelColor(144, 0,255,0);
      pixels.setPixelColor(125, 0,255,0);
      pixels.setPixelColor(129, 0,255,0);
      pixels.setPixelColor(159, 0,255,0);  
    }
    
    pixels.show();
    delay(DELAY);
    if (APDS.gestureAvailable()) {
      int gesture = APDS.readGesture();
      switch (gesture) {
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
    arm_mode==1 ? arm_mode = 2 : arm_mode = 1;
  } while(pixel == ANDROID);
  
};

void showRainbow(){
  // red
  for (int i=42 ; i<48 ; i++) // line1
  {
    pixels.setPixelColor(i,255,0,0);
  }
  for (int i=48 ; i<55 ; i++) // line2
  {
    pixels.setPixelColor(i,255,0,0);
  }
  for (int i=72 ; i<80 ; i++) // line3
  {
    pixels.setPixelColor(i,255,0,0);
  }

  // red + orange
  for (int i=80 ; i<85 ; i++) // line4: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  // red + orange
  for (int i=85 ; i<89 ; i++) // line4: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  // red + orange
  for (int i=106 ; i<112 ; i++) // line5: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  // red + orange
  for (int i=102 ; i<106 ; i++) // line5: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //-------------------------------------

    // red + orange + yellow
  for (int i=112 ; i<116 ; i++) // line6: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=116 ; i<119 ; i++) // line6: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=119 ; i<123 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }
  
  //-------------------------------------

    // red + orange + yellow
  for (int i=139 ; i<144 ; i++) // line7: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=136 ; i<139 ; i++) // line7: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=132 ; i<136 ; i++) // line7: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //-------------------------------------

  // red + orange + yellow + green
  for (int i=144 ; i<147 ; i++)
  {
    pixels.setPixelColor(i,128, 128, 0);
  }
    
  for (int i=147 ; i<150 ; i++)
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=150 ; i<153 ; i++)
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=153 ; i<157 ; i++)
  {
    pixels.setPixelColor(i,255,0,0);
  }
  
  //--------------------------------------------
  // red + orange + yellow + green + blue
  // line8: blue
  {
    pixels.setPixelColor(175, 0, 0, 255);
    pixels.setPixelColor(174, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(173, 0, 255, 0);
    pixels.setPixelColor(172, 0, 255, 0);
  }

  for (int i=169 ; i<172 ; i++)
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=166 ; i<169 ; i++)
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=162 ; i<166 ; i++)
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //--------------------------------------------
  // red + orange + yellow + green + blue
  // line8: blue
  {
    pixels.setPixelColor(176, 0, 0, 255);
    pixels.setPixelColor(177, 0, 0, 255);
    pixels.setPixelColor(178, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(179, 0, 255, 0);
    pixels.setPixelColor(180, 0, 255, 0);
  }

  for (int i=181 ; i<184 ; i++)
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=184 ; i<187 ; i++) // line8: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=187 ; i<190 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //--------------------------------------------
  // red + orange + yellow + green + blue + purple
  // line8: purple
  {
    pixels.setPixelColor(206, 127, 0, 127);
    pixels.setPixelColor(207, 127, 0, 127);
  }
  // line8: blue
  {
    pixels.setPixelColor(205, 0, 0, 255);
    pixels.setPixelColor(204, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(203, 0, 255, 0);
    pixels.setPixelColor(202, 0, 255, 0);
  }

  for (int i=199 ; i<202 ; i++) // line8: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=196 ; i<199 ; i++) // line8: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=194 ; i<196 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //--------------------------------------------
  // red + orange + yellow + green + blue + purple
  // line8: purple
  {
    pixels.setPixelColor(208, 127, 0, 127);
    pixels.setPixelColor(209, 127, 0, 127);
    pixels.setPixelColor(210, 127, 0, 127);
  }
  // line8: blue
  {
    pixels.setPixelColor(211, 0, 0, 255);
    pixels.setPixelColor(212, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(213, 0, 255, 0);
    pixels.setPixelColor(214, 0, 255, 0);
  }

  for (int i=215 ; i<218 ; i++) // line8: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=218 ; i<220 ; i++) // line8: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=220 ; i<222 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //--------------------------------------------
  // red + orange + yellow + green + blue + purple
  // line8: purple
  {
    pixels.setPixelColor(237, 127, 0, 127);
    pixels.setPixelColor(236, 127, 0, 127);
  }
  // line8: blue
  {
    pixels.setPixelColor(235, 0, 0, 255);
    pixels.setPixelColor(234, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(233, 0, 255, 0);
    pixels.setPixelColor(232, 0, 255, 0);
  }

  for (int i=230 ; i<232 ; i++) // line8: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=228 ; i<230 ; i++) // line8: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=226 ; i<228 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }

  //--------------------------------------------
  // red + orange + yellow + green + blue + purple
  // line8: purple
  {
    pixels.setPixelColor(242, 127, 0, 127);
    pixels.setPixelColor(243, 127, 0, 127);
  }
  // line8: blue
  {
    pixels.setPixelColor(244, 0, 0, 255);
    pixels.setPixelColor(245, 0, 0, 255);
  }
  // line8: green
  {
    pixels.setPixelColor(246, 0, 255, 0);
    pixels.setPixelColor(247, 0, 255, 0);
  }

  for (int i=248 ; i<250 ; i++) // line8: yellow
  {
    pixels.setPixelColor(i,128, 128, 0);
  }

  
  for (int i=250 ; i<252 ; i++) // line8: orange
  {
    pixels.setPixelColor(i,170, 85, 0);
  }

  
  for (int i=252 ; i<254 ; i++) // line6: red
  {
    pixels.setPixelColor(i,255,0,0);
  }
  
  pixels.show();
}
void showSnow(){
  int snow_scene = 1;
  int snow_first[15] = {
    0,9,34,45,62,67,75,79,104,133,25,5,59,103,21
  };
  
  int snow_second[15] = {
    31,22,61,50,65,92,84,80,119,154,38,26,68,120,42
  };
  
  int snow_third[15] = {
    32,41,66,77,94,99,107,111,119,165,57,37,91,135,53
  };

  int snow_fourth[15] = {
    63,54,93,82,97,124,116,112,136,186,70,58,100,152,74
  };
  
  do{
    pixels.clear();
    pixels.setBrightness(BRIGHTNESS);
    if (snow_scene == 1)
    {
      for (int i = 0; i<15; i++)
      {
        pixels.setPixelColor(snow_first[i], 255,255,255);
      }  
    }
  
    else if (snow_scene == 2)
    {
      for (int i = 0; i<15; i++)
      {
        pixels.setPixelColor(snow_second[i], 255,255,255);
      }  
    }
  
    else if (snow_scene == 3)
    {
      for (int i = 0; i<15; i++)
      {
        pixels.setPixelColor(snow_third[i], 255,255,255);
      }  
    }
    
    else if (snow_scene == 4)
    {
      for (int i = 0; i<13; i++)
      {
        pixels.setPixelColor(snow_fourth[i], 255,255,255);
      }  
    }
   
  
    // 나무에 눈 쌓인
    pixels.setPixelColor(155, 255,255,255);
    pixels.setPixelColor(131, 255,255,255);
    pixels.setPixelColor(125, 255,255,255);
    pixels.setPixelColor(129, 255,255,255);
    pixels.setPixelColor(159, 255,255,255); 
  
    // 지붕 : blue
    for (int i=116 ; i<119 ; i++)
    {
      pixels.setPixelColor(i, 0,0,255);
    }
    
    for (int i=136 ; i<141 ; i++)
    {
      pixels.setPixelColor(i, 0,0,255);
    }
    
    for (int i=146 ; i<153 ; i++)
    {
      pixels.setPixelColor(i, 0,0,255);
    }
  
    pixels.setPixelColor(174, 0,0,255);
    pixels.setPixelColor(177, 0,0,255);
    pixels.setPixelColor(166, 0,0,255);
    pixels.setPixelColor(185, 0,0,255);
  
  
    // 지붕에 눈 쌓인
    pixels.setPixelColor(174, 255,255,255);
    pixels.setPixelColor(166, 255,255,255);
    pixels.setPixelColor(146, 255,255,255);
    pixels.setPixelColor(152, 255,255,255);
    pixels.setPixelColor(140, 255,255,255);
    pixels.setPixelColor(136, 255,255,255);
    pixels.setPixelColor(116, 255,255,255);
    pixels.setPixelColor(118, 255,255,255);
    pixels.setPixelColor(106, 255,255,255);
  
    // 집 몸통 : orange
    for (int i=167 ; i<174 ; i++)
    {
      pixels.setPixelColor(i, 170,85,0);
    }
    
    for (int i=178 ; i<185 ; i++)
    {
      pixels.setPixelColor(i, 170,85,0);
    }
    
    for (int i=199 ; i<206 ; i++)
    {
      pixels.setPixelColor(i, 170,85,0);
    }
    
    for (int i=210 ; i<217 ; i++)
    {
      pixels.setPixelColor(i, 170,85,0);
    }
  
    // 창문 : 하늘
    pixels.setPixelColor(179, 0,255,255);
    pixels.setPixelColor(204, 0,255,255);
    pixels.setPixelColor(183, 0,255,255);
    pixels.setPixelColor(200, 0,255,255);
  
    // 문 : 빨강 
    pixels.setPixelColor(202, 255,0,0);
    pixels.setPixelColor(213, 255,0,0);
  
    // 나뭇잎 : green
    pixels.setPixelColor(130, 0,255,0);
    pixels.setPixelColor(156, 0,255,0);
    pixels.setPixelColor(157, 0,255,0);
    pixels.setPixelColor(158, 0,255,0);
    for (int i=160 ; i<165 ; i++)
    {
      pixels.setPixelColor(i, 0,255,0);
    }
    pixels.setPixelColor(187, 0,255,0);
    pixels.setPixelColor(188, 0,255,0);
    pixels.setPixelColor(190, 0,255,0);
    pixels.setPixelColor(191, 0,255,0);
    pixels.setPixelColor(193, 0,255,0);
    pixels.setPixelColor(195, 0,255,0);
  
    // 나무 몸통 : brown (0, 50, 100)
    pixels.setPixelColor(189, 181,100,20);
    pixels.setPixelColor(194, 181,100,20);
    pixels.setPixelColor(221, 181,100,20);
    
  
    // 눈 바닥 
    for (int i=224 ; i<256 ; i++)
    {
      pixels.setPixelColor(i, 255,255,255);
    }
  
    pixels.show();
    delay(DELAY);
    if (APDS.gestureAvailable()) {
      int gesture = APDS.readGesture();
      switch (gesture) {
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
    snow_scene==4 ? snow_scene = 1 : snow_scene+=1;
  } while(pixel == SNOW);
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
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  if (Serial.available() > 0) {
    char x = Serial.read();
    if (x == 'b') {
        setFace(2, 0, 127, 0);
    } else if (x == 'c') {
        setFace(4, 255, 0 ,255);
    } else if (x == 'd') {
        setFace(3, 255, 0, 0);
    } else {
        setFace(1, 0, 0 ,255);
    }
  }
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

void showTree() {
  int i=0;
  int red[23]={8, 22, 40, 56, 71, 85, 90, 100, 102, 105, 108, 134, 135, 137, 147, 149, 155, 167, 168, 170, 181, 182, 189};
  int green[33]={23,39,55,70,86,101,106,118,120,133,148,150,151,152,163,166,169,180,183};
  int yellow[33]={24,42,54,72,84,89,119,139,165,173,177,184};
  int blue[33]={38,41,74,88,104,117,121,136,153,164,172,179,185,188};
  int purple[33]={73,103,154,187};
  int lightgreen[33]={87,171,178,186,199,200,201,214,215,216,231,232,233,246,247,248};

  int colorMode=0;
  int colorSet[12][3]={234,51,35,72,161,84,245,194,66,47,111,186,104,54,154,160,205,99,234,51,35,72,161,84,245,194,66,47,111,186,104,54,154,160,205,99};

  do{
    for(i=0;i<23;i++){
      if(red[i] == 0) break;
      pixels.setPixelColor(red[i], colorSet[colorMode][0], colorSet[colorMode][1], colorSet[colorMode][2]);
    }
    for(i=0;i<33;i++){
      if(green[i] == 0) break;
      pixels.setPixelColor(green[i], colorSet[colorMode+1][0], colorSet[colorMode+1][1], colorSet[colorMode+1][2]);
    }
    for(i=0;i<33;i++){
      if(yellow[i] == 0) break;
      pixels.setPixelColor(yellow[i], colorSet[colorMode+2][0], colorSet[colorMode+2][1], colorSet[colorMode+2][2]);
    }
    for(i=0;i<33;i++){
      if(blue[i] == 0) break;
      pixels.setPixelColor(blue[i], colorSet[colorMode+3][0], colorSet[colorMode+3][1], colorSet[colorMode+3][2]);
    }
    for(i=0;i<33;i++){
      if(purple[i] == 0) break;
      pixels.setPixelColor(purple[i], colorSet[colorMode+4][0], colorSet[colorMode+4][1], colorSet[colorMode+4][2]);
    }
    for(i=0;i<33;i++){
      if(lightgreen[i] == 0) break;
      pixels.setPixelColor(lightgreen[i], colorSet[colorMode+5][0], colorSet[colorMode+5][1], colorSet[colorMode+5][2]);
    }
    
    pixels.show();
    delay(DELAY);
    if (APDS.gestureAvailable()) {
      int gesture = APDS.readGesture();
      switch (gesture) {
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
    colorMode==5 ? colorMode = 0 : colorMode+=1;
  } while(pixel == TREE);
}

void setFace(int eyeMouseColor, uint8_t faceR, uint8_t faceG, uint8_t faceB) {

  //third line
  for(int i=21; i<27; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);  
  }

  for(int i=36; i<44; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //4th line
  for(int i=51; i<61; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //5th line
  for(int i=66; i<78; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //5th line
  for(int i=81; i<95; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //6th line
  for(int i=97; i<111; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //6th line
  for(int i=113; i<127; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //th line
  for(int i=129; i<143; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //th line
  for(int i=145; i<159; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }  
  
  //th line
  for(int i=161; i<175; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  //th line
  for(int i=178; i<190; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }  
  
  //th line
  for(int i=195; i<205; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

    //th line
  for(int i=212; i<220; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }  
  
  //th line
  for(int i=229; i<235; i++) {
    pixels.setPixelColor(i,faceR,faceG,faceB);
  }

  if (eyeMouseColor == 1) {
      //merong-eye
      pixels.setPixelColor(85,255,255,255);
      pixels.setPixelColor(86,255,255,255);
      pixels.setPixelColor(90,255,255,255);
      pixels.setPixelColor(89,255,255,255);
      pixels.setPixelColor(101,255,255,255);
      pixels.setPixelColor(102,255,255,255);
      pixels.setPixelColor(105,255,255,255);
      pixels.setPixelColor(106,255,255,255);
    
      //merong-mouse
      for(int i=181; i<187; i++) {
        pixels.setPixelColor(i,255,255,255);  
      }
  }

  else if (eyeMouseColor == 2) {
       //happy-eye
    pixels.setPixelColor(69,255,255,255);
    pixels.setPixelColor(74,255,255,255);
    pixels.setPixelColor(84,255,255,255);
    pixels.setPixelColor(86,255,255,255);
    pixels.setPixelColor(89,255,255,255);
    pixels.setPixelColor(91,255,255,255);
  
    //happy-mouse
    pixels.setPixelColor(148,255,255,255);
    pixels.setPixelColor(155,255,255,255);
    pixels.setPixelColor(165,255,255,255);
    pixels.setPixelColor(170,255,255,255);
    pixels.setPixelColor(182,255,255,255);
    pixels.setPixelColor(183,255,255,255);
    pixels.setPixelColor(184,255,255,255);
    pixels.setPixelColor(185,255,255,255);
  }

  else if (eyeMouseColor == 3) {
       //happy-eye
    pixels.setPixelColor(67,255,255,255);
    pixels.setPixelColor(68,255,255,255);
    pixels.setPixelColor(75,255,255,255);
    pixels.setPixelColor(76,255,255,255);
    pixels.setPixelColor(85,255,255,255);
    pixels.setPixelColor(90,255,255,255);
    pixels.setPixelColor(117,255,255,255);
    pixels.setPixelColor(122,255,255,255);
  
    //happy-mouse
    pixels.setPixelColor(167,255,255,255);
    pixels.setPixelColor(168,255,255,255);
    pixels.setPixelColor(182,255,255,255);
    pixels.setPixelColor(185,255,255,255);
    pixels.setPixelColor(197,255,255,255);
    pixels.setPixelColor(202,255,255,255);
}

else if (eyeMouseColor == 4) {
      //shocking-eye
      pixels.setPixelColor(85,255,255,255);
      pixels.setPixelColor(86,255,255,255);
      pixels.setPixelColor(90,255,255,255);
      pixels.setPixelColor(89,255,255,255);
      pixels.setPixelColor(101,255,255,255);
      pixels.setPixelColor(102,255,255,255);
      pixels.setPixelColor(105,255,255,255);
      pixels.setPixelColor(106,255,255,255);
    
      //shocking-mouse

      pixels.setPixelColor(166,255,255,255);
      pixels.setPixelColor(167,255,255,255);
      pixels.setPixelColor(168,255,255,255);
      pixels.setPixelColor(169,255,255,255);
      
      pixels.setPixelColor(182,255,255,255);
      pixels.setPixelColor(183,255,255,255);
      pixels.setPixelColor(184,255,255,255);
      pixels.setPixelColor(185,255,255,255);

      pixels.setPixelColor(198,255,255,255);
      pixels.setPixelColor(199,255,255,255);
      pixels.setPixelColor(200,255,255,255);
      pixels.setPixelColor(201,255,255,255);
 }

 
  pixels.show();
};