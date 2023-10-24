#include <Adafruit_NeoPixel.h>
 
#define PIN 4
#define DOOR_SENSOR 2


bool isRingOn = true;

int numberOfRingColors = 3;

uint32_t ringColors[] = {
  Adafruit_NeoPixel::Color(255, 0, 0),
  Adafruit_NeoPixel::Color(0, 255, 0),
  Adafruit_NeoPixel::Color(0, 0, 255)
};

int ringColorIndex = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  Serial.begin(9600);
  pinMode(DOOR_SENSOR, INPUT_PULLUP);
  strip.begin();
  strip.setBrightness(60); //adjust brightness here
  strip.show();
  cleanRing();
}
 
void loop() {
  int proximity = digitalRead(DOOR_SENSOR);

  bool requiredRingState = proximity == HIGH;
  if (requiredRingState) {
    Serial.println("Door opened");
    ringColorIndex %= numberOfRingColors;
    alarmRing(ringColorIndex++);
  } else {
    ringColorIndex = 0;
    Serial.println("Door closed");
    cleanRing();
    delay(1000);
  }
  
}

void cleanRing() {
  for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void alarmRing(int colorIndex) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, ringColors[colorIndex]);
    strip.show();
    delay(30);
  }
}
