#include <LiquidCrystal.h>

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
#include <Servo.h> 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
Servo servo1;
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 7,6,5,4);
void setup() {
  Serial.begin(9600);
  
  //Serial.println(F("DHTxx test!"));
lcd.begin(16, 2); 
//lcd.setCursor(0, 0);
//lcd.print("hello, world!");
servo1.attach(9); 
  dht.begin();
}

int pos = 0;  // Stores the position (angle) of the servo. Range is [0, 180].
void loop() {
  
  // Wait a few seconds between measurements.
  delay(2000);
//lcd.setCursor(0, 1);

  if (Serial.available()) {  // Returns true if there is serial input.
    char ch = Serial.read();
    
    if (ch == 'e') {
      // Make sure not to exceed the mechanical limitation.
      if (pos < 60) {
        pos += 1;
      }
    } else {
      // Make sure not to exceed the mechanical limitation.
      if (pos > 0) {
        pos -= 1;
      }
    }
    
    servo1.write(pos);
    
    delay(50);
  }
  else{
//lcd.print(millis()/1000);
int lightValue = analogRead(A0);
//Serial.print(lightValue);
//Serial.print(" ");
// map the light readings to the angle possible by the servo motor 
lightValue = map (lightValue, 0, 1023, 0, 180);

// control the servo motor based on the light value read, adjust linearly by angles 
servo1.write (lightValue); 
  }
delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
   // Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  //Serial.print(F("Humidity: "));
  //Serial.print(h);
  
  //Serial.print(F("%  Temperature: "));
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  //Serial.print(t);
  //Serial.print(F("°C "));
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
/*
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));*/
}
