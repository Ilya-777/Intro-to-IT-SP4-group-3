//Working temperature and humidity and soiul sensor on BLYNK app, relay issues
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> //ESP library
#include <BlynkSimpleEsp8266.h> //BLYNK library
#include <DHT.h>  //DHT11 library

int soilSensorPin=A0; //locate moisture sensor pin
int sensorvalue; //define name
int soilSensor; //define name
int humidity; //define name
int temperature; //define name
int relayPinFan = 12; // pin number for fan relay
int relayPinPump = 13; // pin number for water pump relay

const int dry = 643; // value for dry sensor, 0%
const int wet = 296; // value for wet sensor, 100%

char auth[] = "ssJ0DkToCt1cki5H07DZ1WYBUEGBCuxk"; // BLYNK Automated greenhouse project
char ssid[] = "CASA_2G";
char pass[] = "Jasmine777";

#define DHTPIN 14          // DHT11 nodeMCU on pin D5 / GPIO14
#define DHTTYPE DHT11     //Type of temperature / humidity sensor

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer; //Announcing timer for sending data to cloud


  void sendSensor() //move all Arduino "void loop" code to here for BLYNK compatability
{
  float humidity = dht.readHumidity(); //allow decimal values
  float temperature = dht.readTemperature();  //allow decimal values
  sensorvalue=analogRead(soilSensorPin); //read pin connected to soil moisture sensor
  soilSensor=map(sensorvalue,wet,dry,100,0); // change output reading to a percentage


  if (isnan(humidity) || isnan(temperature)) //check if DHT is responding or not
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    Blynk.virtualWrite(V5, temperature); //send temperature data to BLYNK
    Blynk.virtualWrite(V6, humidity); //send humidity data to BLYNK
    Blynk.virtualWrite(V1, soilSensor); //send soil moisture data to BLYNK


 //Set points for fan on/off
 if (humidity >= 65) {
  digitalWrite(relayPinFan, HIGH); //fan on
  }
 else
 {
    digitalWrite(relayPinFan, LOW); //fan off
 }
 //Set points for pump on/off
  if (soilSensor <= 70) {
    digitalWrite(relayPinPump, HIGH); //pump on
  }
 else
 {
    digitalWrite(relayPinPump, LOW);//pump off
 }
 }

void setup()
{
  Serial.begin(9600); //Turn on serial monitor
  Blynk.begin(auth, ssid, pass); //connect to cloud
  dht.begin(); //turn on temperature sensor
  timer.setInterval(1000L, sendSensor); //send data to cloud every 1 second

  pinMode(relayPinFan, OUTPUT); //assign fan relay pin as an output
  pinMode(relayPinPump, OUTPUT);//assign water pump relay pin as an output
}

void loop()
{
 Blynk.run();
 timer.run();
}
