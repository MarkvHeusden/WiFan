#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

char ssid[] = "???";       // REPLACE with your network SSID (name)
char password[] = "???";  // REPLACE with your network key
int relay = D7;

// For HTTPS requests
WiFiClientSecure client;


// Just the base of the URL you want to connect to
#define HOST "api.openweathermap.org"

void setup() {
  //Relay setup
  pinMode(relay, OUTPUT);
  
  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  //--------

  // If you don't need to check the fingerprint
   client.setInsecure();
}

void makeHTTPRequest() {

  // Opening connection to server (Use 80 as port if HTTP)
  if (!client.connect(HOST, 443))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  // give the esp a breather
  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  // REPLACE LOCATION AND APIKEY WITH YOUR OWN
  client.print("/data/2.5/weather?q=Yucatan&appid=*******API_KEY_HERE*******&units=metric"); // %2C == ,
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return;
  }
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return;
  }

  //Use the ArduinoJson Assistant to calculate this:

  //StaticJsonDocument<192> doc;
  DynamicJsonDocument doc(1024); //For ESP32/ESP8266 you'll mainly use dynamic.

  DeserializationError error = deserializeJson(doc, client);

  if (!error) {
    float temp = doc["main"]["temp"];
    String location = doc["name"];

    Serial.print("Temperature in ");
    Serial.print(location);
    Serial.print(": ");
    Serial.println(temp);

    if (temp < 25) {
      digitalWrite(relay, LOW);
      Serial.println("Fan turned off");
  } else {
      digitalWrite(relay, HIGH);
      Serial.println("Fan turned on");
  }
    
    
  } else {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
}

void loop() {
  makeHTTPRequest();
  delay(50000);
}
