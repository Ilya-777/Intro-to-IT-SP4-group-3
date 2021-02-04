
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;


//int soil = analogRead(A0);
const int dry = 643; // value for dry sensor
const int wet = 296; // value for wet sensor

char auth[] = "ssJ0DkToCt1cki5H07DZ1WYBUEGBCuxk"; // Greenhouse
char ssid[] = "CASA_2G";
char pass[] = "Jasmine777";
 
#define DHTPIN 14          // D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 // float s = map(soil,wet, dry, 100, 0);
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  //Blynk.virtualWrite(V7, s);
  
}
 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,wet,dry,100,0); //100,0 pottupaaru
  delay(1000);
  Blynk.run();
   Blynk.virtualWrite(V1,outputvalue);
  timer.run();
}
