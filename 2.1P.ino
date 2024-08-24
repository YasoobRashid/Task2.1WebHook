#include <WiFiNINA.h>
#include "ThingSpeak.h"
#include "DHT.h"

#define DHTPIN 2       // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "Jazil's S24";
char pass[] = "8899111719";

WiFiClient client;
unsigned long myChannelNumber = 2630940;
const char * myWriteAPIKey = "FI9DWR9MYXDKUQWC";

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Data successfully sent to ThingSpeak");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }

  delay(60000);  // Wait 60 seconds before sending the next update
}
