
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>


const int DATA_PIN = 12;
const int PIXEL_NUM = 2;      // number of pixels
const int DEELAY = 100;

const int BRIGHTNESS = 40;   // 0-255
const int WAIT = 50;
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_NUM, DATA_PIN, NEO_GRB + NEO_KHZ800);
float newe;
float olde;
float olde_x;
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


  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");
  newe = (float) event.acceleration.x + (float) event.acceleration.y + (float) event.acceleration.z;
  //avgaccel2 = (float) 5;

  Serial.println();

  Serial.println("Olde value is "); Serial.println(olde);
  Serial.println("your newe is "); Serial.println(newe);
  Serial.println(); Serial.println();
  float avgvalue;
  avgvalue =  ((float)(olde + newe) / 2);
  Serial.println("your average is "); Serial.println(avgvalue);
  Serial.println("olde value is "); Serial.println(olde);

  Serial.println();

  //Z dimensions
  float zvar = float abs (event.acceleration.z);
  float zvar_o = event.acceleration.z;
  Serial.print("Zvar is "); Serial.println(zvar);
  Serial.print("original zvar was "); Serial.println(zvar_o);

  Serial.println();

  //X dimension
  float yvar = float abs (event.acceleration.y);
  float yvar_o = event.acceleration.y;
  Serial.print("Yvar is "); Serial.println(yvar);
  Serial.print("original yvar was "); Serial.println(yvar_o);

  Serial.println();

  //Y dimension
  float xvar = float abs (event.acceleration.x);
  float xvar_o = event.acceleration.x;
  Serial.print("xvar is "); Serial.println(xvar);
  Serial.print("original xvar was "); Serial.println(xvar_o);


  // some average movements
  float average = (float) ((xvar + yvar + zvar) / 3);
  Serial.println("Average value of all 3 in abs value is "); Serial.println(average);


  theChange = float abs (average - olde);

  /*strip.setPixelColor(0, 255, 255, 50);
    strip.show();*/
  /* Delay before the next sample */
  Serial.println("The change in stuff is "); Serial.println(theChange);
  Serial.println("Method testing "); Serial.println(velocityMath(xvar_o, olde_x, yvar_o, olde_y, zvar_o, olde_z));
  Serial.println("----------------------------------------------------------------");
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
  delay(DEELAY);
  if (counter >= 0) { // every 300 cycles the thing resets. whill change depending on deelay. for this it'll be 30 sec of activity.
      counter = counter - 1;
    } else {
      counter = 300;
      greene = 0;
      redde = 0;
      Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();
      }
}

/*void rainbow(uint8_t wait) {
  uint16_t i, j;
  strip.setPixelColor(255, 255, 255, 50);

    strip.show();
    delay(wait);
  }*/
void colorChanger(float change) {
  float val = change * 100;
  if (counter > 254) {
    strip.setPixelColor(1, 148,0,254);}
    else {
  strip.setPixelColor(1, 148,0,counter);
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

void brightChanger(float change) {
    // do this later
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

/*float actin(float greene, float redde) {
  if (greene > redde) {
    Serial.println("ACTIVE ACTIVE ACTIVE ACTIVE ACTIVE ACTIVE ACTIVE");
    return 0;
  } else {
    Serial.println( "MOVE MOVE MOVE MOVE MOVE MOVE MOVE MOVE MOVE");
    return 1;
  }
  return 0;
  }*/
