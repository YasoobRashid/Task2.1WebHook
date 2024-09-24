#include <WiFiNINA.h>
#include "ThingSpeak.h"
#include "DHT.h"

#define DHTPIN 2       // Pin where the DHT22 is connected
#define DHTTYPE DHT22  // DHT 22
DHT dht(DHTPIN, DHTTYPE); // Create an instance of the DHT sensor

char ssid[] = "Jazil's S24"; // Your Wi-Fi SSID (network name)
char pass[] = "8899111719";   // Your Wi-Fi password

WiFiClient client; // Create a WiFiClient object to handle communication with ThingSpeak
unsigned long myChannelNumber = 2630940; // Define your ThingSpeak channel number
const char * myWriteAPIKey = "FI9DWR9MYXDKUQWC"; // Define your ThingSpeak write API key

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
  dht.begin(); // Initialize the DHT sensor
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, pass); // Start the Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) { // Wait until the Wi-Fi is connected
    delay(500); // Wait half a second before checking again
    Serial.print("."); // Print a dot to indicate progress
  }
  Serial.println("\nConnected to Wi-Fi"); // Print a message once connected
  
  ThingSpeak.begin(client); // Initialize ThingSpeak with the WiFi client
}

void loop() {
  // Read humidity and temperature from the DHT sensor
  float h = dht.readHumidity(); // Get the humidity value
  float t = dht.readTemperature(); // Get the temperature value

  // Check if reading was unsuccessful
  if (isnan(h) || isnan(t)) { // If the readings are not a number (NaN)
    Serial.println("Failed to read from DHT sensor!"); // Print error message
    return; // Exit the loop
  }

  // Print the values to the Serial Monitor
  Serial.print("Humidity: "); // Print the humidity label
  Serial.print(h); // Print the humidity value
  Serial.print(" %\t"); // Print percentage symbol
  Serial.print("Temperature: "); // Print the temperature label
  Serial.print(t); // Print the temperature value
  Serial.println(" °C"); // Print degree Celsius symbol

  // Set the fields to be written to ThingSpeak
  ThingSpeak.setField(1, t); // Set field 1 to temperature value
  ThingSpeak.setField(2, h); // Set field 2 to humidity value

  // Write the fields to ThingSpeak
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // Send data to ThingSpeak
  if (x == 200) { // Check if the response is successful (HTTP status 200)
    Serial.println("Data successfully sent to ThingSpeak"); // Print success message
  } else {
    Serial.println("Error sending data to ThingSpeak"); // Print error message
  }

  delay(60000); // Wait for 60 seconds before the next loop iteration
}
