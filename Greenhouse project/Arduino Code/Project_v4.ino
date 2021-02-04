//project_v1 includes Soil sensor with percentage value, DHT11,LCD,Relay and fan
#include <LiquidCrystal_I2C.h> //LCD library
#include "DHT.h"
#define DHTPIN 2 //Temperature and humidity sensor, grey wire
#define DHTTYPE DHT11 // Type of humidity sensor

const int dry=669; // capacitive moisture sensor in air
const int wet=315; // capacitive moisture sensor in water
int relayPinFan=9;  // relay module for fan, yellow
int relayPinPump=8; // relay module for water pump, green
int soilSensor=A0;  // capacitive soil moisture sensor, brown
int soilVal;
int percentage;

int dt=3000; // Time delay

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600); //initialise serial monitor
  dht.begin();     // initialize the temperature and humidity sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight
  pinMode(relayPinFan, OUTPUT); // define pin connected to relay as an output
  pinMode(relayPinPump, OUTPUT); // define pin connected to relay as an output
  pinMode(soilSensor,INPUT); //define pin connected to soil moisture sensor as input
  delay(dt);
}

void loop()
{
  //delay(dt); // wait a few seconds between measurements

  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature



  // This section for printing the temperature and humidity on the LCD
  lcd.clear(); // clear LCD screen

  if (isnan(humi) || isnan(tempC)) { // check if any reads failed
    lcd.setCursor(0, 0);
    lcd.print("Failed to read sensor");
  } else {
    lcd.setCursor(0, 0);  // print begins at the first row
    lcd.print("Temp:  ");
    lcd.print(tempC);     // print temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");

    lcd.setCursor(0, 1);  // print at the second row
    lcd.print("Humid: ");
    lcd.print(humi);      // print humidity
    lcd.print("%");       // print % character

     //This section trigger fan relay
 }
  if(humi>=65){
    digitalWrite(relayPinFan,HIGH);
  }
  if(humi<=64){
   digitalWrite(relayPinFan,LOW);
  }

  //This section trigger water pump relay
 if(percentage<=80){
    digitalWrite(relayPinPump,HIGH); //turn water off
  }
  if(percentage>=80){ //turn water pump on
    digitalWrite(relayPinPump,LOW);
}

    delay(dt);            // wait a few seconds between measurements

// This section for printing the temperature and humidity on the LCD
  lcd.clear();
    int sensorVal = analogRead(A0);
    int percentageHumididy = map(sensorVal, wet, dry, 100, 0);
  Serial.println(sensorVal);
  Serial.print(percentageHumididy);
  Serial.println("%");
  lcd.print("Soil/Water ");
  lcd.print(percentageHumididy);
  lcd.println("%   ");


delay(dt);
}
