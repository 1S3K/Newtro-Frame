// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        12 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 256 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setBigHeart() {
  //first line
  pixels.setPixelColor(36,255,0,0);
  pixels.setPixelColor(37,255,0,0);
  pixels.setPixelColor(42,255,0,0);
  pixels.setPixelColor(43,255,0,0);

  //second line
  pixels.setPixelColor(51,255,0,0);
  pixels.setPixelColor(52,255,0,0);
  pixels.setPixelColor(53,255,0,0);
  pixels.setPixelColor(54,255,0,0);
  pixels.setPixelColor(57,255,0,0);
  pixels.setPixelColor(58,255,0,0);
  pixels.setPixelColor(59,255,0,0);
  pixels.setPixelColor(60,255,0,0);

  //third line
  for(int i=66; i<78; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //4th line
  for(int i=81; i<95; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //5th line
  for(int i=97; i<111; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=113; i<127; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=130; i<142; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //th line
  for(int i=147; i<157; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }
  
  //th line
  for(int i=164; i<172; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

      //th line 
  for(int i=181; i<187; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

        //th line
  for(int i=198; i<202; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  pixels.setPixelColor(215,255,0,0);  
  pixels.setPixelColor(216,255,0,0); 
 
  pixels.show();
};

void setSmallHeart() {
  //first line
  pixels.setPixelColor(53,255,0,0);
  pixels.setPixelColor(54,255,0,0);
  pixels.setPixelColor(57,255,0,0);
  pixels.setPixelColor(58,255,0,0);

  //second line
  pixels.setPixelColor(68,255,0,0);
  pixels.setPixelColor(69,255,0,0);
  pixels.setPixelColor(70,255,0,0);
  pixels.setPixelColor(71,255,0,0);
  pixels.setPixelColor(72,255,0,0);
  pixels.setPixelColor(73,255,0,0);
  pixels.setPixelColor(74,255,0,0);
  pixels.setPixelColor(75,255,0,0);

  //third line
  for(int i=83; i<93; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //4th line
  for(int i=99; i<109; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //5th line
  for(int i=115; i<125; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=132; i<140; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=149; i<155; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //th line
  for(int i=166; i<170; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  pixels.setPixelColor(183,255,0,0);  
  pixels.setPixelColor(184,255,0,0); 
 
  pixels.show();
};

void setMiddleHeart() {
  //first line
  pixels.setPixelColor(37,255,0,0);
  pixels.setPixelColor(38,255,0,0);
  pixels.setPixelColor(41,255,0,0);
  pixels.setPixelColor(42,255,0,0);

  //second line
  pixels.setPixelColor(52,255,0,0);
  pixels.setPixelColor(53,255,0,0);
  pixels.setPixelColor(54,255,0,0);
  pixels.setPixelColor(55,255,0,0);
  pixels.setPixelColor(56,255,0,0);
  pixels.setPixelColor(57,255,0,0);
  pixels.setPixelColor(58,255,0,0);
  pixels.setPixelColor(59,255,0,0);

  //third line
  for(int i=67; i<77; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //4th line
  for(int i=82; i<94; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //5th line
  for(int i=98; i<110; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //5th line
  for(int i=114; i<126; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=131; i<141; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //6th line
  for(int i=148; i<156; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  //th line
  for(int i=165; i<171; i++) {
    pixels.setPixelColor(i,255,0,0);  
  }

  
  pixels.setPixelColor(182,255,0,0);  
  pixels.setPixelColor(183,255,0,0); 
  
  pixels.setPixelColor(184,255,0,0);  
  pixels.setPixelColor(185,255,0,0); 


  pixels.setPixelColor(199,255,0,0);  
  pixels.setPixelColor(200,255,0,0); 
 
  pixels.show();
};

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

void setAndroidRobot(uint8_t faceR, uint8_t faceG, uint8_t faceB) {

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
  
  pixels.show();
};

void snowingHouse() {

  for (int i=210 ; i<217 ; i++)
  {
    pixels.setPixelColor(i, 170,85,0);
  }
  
  for (int i=224 ; i<256 ; i++)
  {
    pixels.setPixelColor(i, 255,0,255);
  }

  pixels.show();
}

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  
//  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setBrightness(3);

//  snowingHouse();


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
//setAndroidRobot(0, 255, 255);
  
}
