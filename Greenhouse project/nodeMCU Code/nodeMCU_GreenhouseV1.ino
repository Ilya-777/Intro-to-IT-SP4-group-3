//merge arduino code to nodeMCU code
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

const int dry = 643; // value for dry sensor
const int wet = 296; // value for wet sensor
int relayPinFan = 12; // relay for fan, yellow
int relayPinPump = 13; //relay for water pump, green
int sensorVal;
int percentage;

char auth[] = "gCLtm3EcoBpMG3mSaYSzSHh4_BWo_c7I";
char ssid[] = "CASA_2G";
char pass[] = "Jasmine777";

#define DHTPIN 14          // D5 on nodeMCU
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
//void sendSensor()

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit


  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
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
  Blynk.run();
  timer.run();

   // Print sensor data to serial monitor for diagnostics
//   if (isnan(humi) || isnan(tempC)) {
    //lcd.setCursor(0, 0);
   // lcd.print("Failed");

  }
     sensorVal = analogRead(A0);
     percentage = map(sensorVal, wet, dry, 100, 0);

}
