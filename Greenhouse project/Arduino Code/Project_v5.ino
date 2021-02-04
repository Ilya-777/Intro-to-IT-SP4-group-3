//project_v5 refines soil sensor,  DHT11,LCD,Relay and fan
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2 //grey
#define DHTTYPE DHT11
int mSensor = A0; //capacitive moisture sensor, brown
int soilM;       // moisture sensor data readout
int percentage;  // convert moisture sensor data to a percentage
const int moisture_min = 630; // sensor dry
const int moisture_max = 230; // sensor wet
int relayPinFan = 9; // relay for fan, yellow
int relayPinPump = 8; //relay for water pump, green
int dt = 2000;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight
  pinMode(relayPinFan, OUTPUT);
  pinMode(relayPinPump, OUTPUT);
  pinMode(mSensor, INPUT);
  //delay(dt);
}

void loop()
{
  //delay(dt); // wait a few seconds between measurements
  //Humidity sensor
  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature
  if (humi >= 68) {
    digitalWrite(relayPinFan, HIGH);
  }
  if (humi <= 67) {
    digitalWrite(relayPinFan, LOW);
  }
  // print Humidity sensor data to LCD
  Serial.println(soilM);
  lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp:  ");
    lcd.print(tempC);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");

    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Humid: ");
    lcd.print(humi);      // print the humidity
    lcd.print("%");

    delay(dt);


    // soil sensor
    soilM = analogRead(mSensor);
    percentage = map(soilM, moisture_min, moisture_max, 0, 100);
    lcd.clear();
    lcd.print("Soil/Water ");
    lcd.print(percentage);
    lcd.println("%   ");
  }

  if (percentage <= 70) {
    digitalWrite(relayPinPump, HIGH); //turn water off
  }
  if (percentage >= 71) { //turn water pump on
    digitalWrite(relayPinPump, LOW);
  }
  delay(dt);
}
