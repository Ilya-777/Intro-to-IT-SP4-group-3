//project_v6 refines soil sensor,  DHT11,LCD,Relays for water pump and fan
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2 //grey
#define DHTTYPE DHT11
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);
const int dry = 510; // value for dry sensor
const int wet = 233; // value for wet sensor
int relayPinFan = 9; // relay for fan, yellow
int relayPinPump = 8; //relay for water pump, green
int sensorVal;
int percentage;
int dt = 2000;


void setup()
{
  
  Serial.begin(9600);
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight
  pinMode(relayPinFan, OUTPUT);
  pinMode(relayPinPump, OUTPUT);
 }

void loop()
{
  //Humidity sensor
  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature


// print Temperature and Humidity sensor data to LCD
   lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp: ");
    lcd.print(tempC);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");

    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Humidity: ");
    lcd.print(humi);      // print the humidity
    lcd.print("%");

    delay(dt);
  }
  // print soil sensor data to LCD
    sensorVal = analogRead(A0);
    percentage = map(sensorVal, wet, dry, 100, 0);
   Serial.println(sensorVal);
    lcd.clear();
    lcd.print("Water/Soil: ");
    lcd.print(percentage);
    lcd.println("%   ");
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
