//project_v1 includes DHT 11,LCD, and fan relay, no pump relay
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
const int relayPin=A0;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight
  pinMode(relayPin, OUTPUT);
}

void loop()
{
  delay(2000); // wait two seconds between measurement

  float humi  = dht.readHumidity();    // read humidity
  float tempC = dht.readTemperature(); // read temperature

  lcd.clear();
  // check if reading the DHT sensor failed
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
  }
  if(humi>=60){
    digitalWrite(relayPin,HIGH);
  }
  if(humi<=59){
    digitalWrite(relayPin,LOW);
  }
}
