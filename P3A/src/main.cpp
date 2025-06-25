#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "Nautilus";  // Enter your SSID here
const char* password = "20000Leguas";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is default)

// Prototipo de la función handle_root
void handle_root();

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your Wi-Fi modem
  WiFi.begin(ssid, password);

  // Check Wi-Fi is connected to the network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  // Show ESP32 IP on serial

  server.on("/", handle_root);  // Enlaza la URL con la función handle_root
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root URL (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
