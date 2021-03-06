
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
// whoot github is cool

const int DATA_PIN = 12;
const int PIXEL_NUM = 2;      // number of pixels
const int DEELAY = 100;

const int BRIGHTNESS = 40;   // 0-255
const int WAIT = 50;
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_NUM, DATA_PIN, NEO_GRB + NEO_KHZ800);
float newe;
float olde;
float olde_x; // added another change mm
float olde_y;
float olde_z;
float theChange;
int counter = 300;

float greene;
float redde;

void setup(void)
{
#ifndef ESP8266
  while (!Serial);
#endif
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
  }

  /* Display some basic information on this sensor */
  //displaySensorDetails();

  pinMode(DATA_PIN, INPUT);
  digitalWrite(DATA_PIN, HIGH);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);

}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);
  //rainbow(WAIT);
  Serial.println("----------------------------------------------------------------");



  float zvar_o = event.acceleration.z;



  float yvar_o = event.acceleration.y;



  float xvar_o = event.acceleration.x;

  colorChanger(velocityMath(xvar_o, olde_x, yvar_o, olde_y, zvar_o, olde_z));
  if (greene > redde) {
    Serial.println("ACTIVE WOOOOOOT");
  } else {
    Serial.println("MOVE MOVE MOVE MOVE");
  }
  // setting the olde global variables at the end so i can compare them on next loop
  olde = average;
  olde_x = xvar_o;
  olde_y = yvar_o;
  olde_z = zvar_o;
  if (counter >= 0) { // every 300 cycles the thing resets. whill change depending on deelay. for this it'll be 30 sec of activity.
    counter = counter - 1;
  } else {
    counter = 300;
    greene = 0;
    redde = 0;
    Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println(); Serial.println();
  }

  delay(DEELAY);
}

void colorChanger(float change) {
  float val = change * 100;
  if (counter > 254) {
    strip.setPixelColor(1, 148, 0, 254);
  }
  else {
    strip.setPixelColor(1, 148, 0, counter);
  }
  if (val > 15) { // changin fast is green
    strip.setPixelColor(0, 0, 128, 0);
    strip.show();
    greene = greene + 1;
    redde = redde - 1;
  }
  else { // changin slow is red
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    redde = redde + 1;
    greene = greene - 1;
  }
}

float velocityMath(float x1, float x2, float y1, float y2, float z1, float z2) {
  float avvg;
  float d_x = float abs(x1 - x2);
  float d_y = float abs(y1 - y2);
  float d_z = float abs(z1 - z2);
  avvg = d_x + d_y + d_z;
  avvg = avvg / DEELAY;
  return avvg;
}
