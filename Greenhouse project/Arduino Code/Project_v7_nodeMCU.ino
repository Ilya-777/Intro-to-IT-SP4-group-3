//merge arduino code to suit nodeMCU

//#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
#include "DHT.h"
#define DHTPIN 14 //grey
#define DHTTYPE DHT11
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "gCLtm3EcoBpMG3mSaYSzSHh4_BWo_c7I";
char ssid[] = "CASA_2G";
char pass[] = "Jasmine777";

//LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
const int dry = 643; // value for dry sensor
const int wet = 296; // value for wet sensor
int relayPinFan = 12; // relay for fan, yellow
int relayPinPump = 13; //relay for water pump, green
int sensorVal;
int percentage;
int dt = 2000;



void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();     // initialize the sensor

 // Wire.begin(D2, D1); // remember to reverse if changin pins
  //lcd.begin();      // initialize the lcd
  //lcd.backlight(); // open the backlight
  //lcd.home();
  pinMode(relayPinFan, OUTPUT);
  pinMode(relayPinPump, OUTPUT);
 }

void loop()
{

  Blynk.run();
  timer.run();

  //Humidity sensor
  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature


// print Temperature and Humidity sensor data to LCD
  // lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
  Serial.println("Failed to read from DHT sensor!");
    return;

     }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, tempC);
  Blynk.virtualWrite(V6, humi);
}
    //lcd.setCursor(0, 0);
   // lcd.print("Failed");
 else {
//      lcd.setCursor(0, 0);  // start to print at the first row
//      lcd.print("Temp: ");
//      lcd.print(tempC);     // print the temperature
//      lcd.print((char)223); // print ° character
//      lcd.print("C");
//
//      lcd.setCursor(0, 1);  // start to print at the second row
//      lcd.print("Humidity: ");
//      lcd.print(humi);      // print the humidity
//      lcd.print("%");

     // Print sensor data to serial monitor for diagnostics
      Serial.print("Temp: ");
      Serial.print(tempC);     // print the temperature
      Serial.println("C");
      Serial.print("Humidity: ");
      Serial.print(humi);      // print the humidity
      Serial.println("%");
       delay(dt);
  }
     sensorVal = analogRead(A0);
     percentage = map(sensorVal, wet, dry, 100, 0);
    Serial.print("Raw sensor val: ");
    Serial.println(sensorVal);
    Serial.println(" ");
//    lcd.clear();
//    lcd.print("Water/Soil: ");
//    lcd.print(percentage);
//    lcd.println("%   ");

    Serial.print("Water/Soil: ");
    Serial.print(percentage);
    Serial.println("%   ");
 delay(dt);
if (humi >= 58) {
  digitalWrite(relayPinFan, HIGH);
  }
 if (humi <= 57) {
    digitalWrite(relayPinFan, LOW);
 }
  if (percentage <= 70) {
    digitalWrite(relayPinPump, HIGH); //turn water off
  }
  if (percentage >= 71) { //turn water pump on
    digitalWrite(relayPinPump, LOW);
  }
  }
