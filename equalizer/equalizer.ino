#include <PDM.h>
#include <Adafruit_NeoPixel.h>

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

void setup() {
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
}

void loop() {
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
}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}