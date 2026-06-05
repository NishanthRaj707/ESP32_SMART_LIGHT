/*
 * ESP32 Access Point - Web Controlled Relay
 * Using ESPAsyncWebServer on Pin 4
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// 1. Define your Access Point Credentials
const char* ssid = "ESP32_Smart_Light";
const char* password = "12345678"; 

// 2. Define the Relay Pin and State
const int relayPin = 4;
String relayState = "OFF";

// 3. Initialize the Async Web Server on port 80
AsyncWebServer server(80);

// 4. Function to generate the HTML page dynamically
String getHTML(String status) {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f4f4f9; }";
  html += "h1 { color: #333; }";
  html += "p { font-size: 20px; color: #555; }";
  html += ".btn { padding: 15px 40px; font-size: 22px; text-decoration: none; border-radius: 8px; color: white; margin: 10px; display: inline-block; font-weight: bold; }";
  html += ".on { background-color: #28a745; box-shadow: 0 4px #1e7e34; }";
  html += ".off { background-color: #dc3545; box-shadow: 0 4px #a71d2a; }";
  html += ".on:active { background-color: #1e7e34; transform: translateY(2px); }";
  html += ".off:active { background-color: #a71d2a; transform: translateY(2px); }";
  html += "</style></head>";
  
  html += "<body>";
  html += "<h1>ESP32 Smart Light</h1>";
  html += "<p>Light Status: <b>" + status + "</b></p>";
  
  // Create the ON and OFF buttons
  html += "<a href=\"/on\" class=\"btn on\">Turn ON</a>";
  html += "<a href=\"/off\" class=\"btn off\">Turn OFF</a>";
  
  html += "</body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);
  
  // Set the relay pin as an output and turn it OFF initially
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); 
  
  // Start the ESP32 as an Access Point
  Serial.println("Starting Access Point...");
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Define the Web Routing 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getHTML(relayState));
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(relayPin, HIGH); // Turn relay ON
    relayState = "ON";
    request->send(200, "text/html", getHTML(relayState));
    Serial.println("Relay turned ON");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(relayPin, LOW); // Turn relay OFF
    relayState = "OFF";
    request->send(200, "text/html", getHTML(relayState));
    Serial.println("Relay turned OFF");
  });

  // Start the server
  server.begin();
  Serial.println("Async Web Server Started.");
}

void loop() {
  // Loop remains completely empty!
}
