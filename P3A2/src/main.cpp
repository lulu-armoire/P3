#include <WiFi.h>
#include <WebServer.h>  // Biblioteca para el servidor web

const char* ssid = "Nautilus";  // Nombre de tu red Wi-Fi
const char* password = "20000Leguas";  // Contraseña de tu Wi-Fi

WebServer server(80);  // Inicializa el servidor web en el puerto 80

// Configuración opcional de IP estática (descomenta si tienes problemas de conexión)
// IPAddress local_IP(192, 168, 1, 200); // Dirección IP fija
// IPAddress gateway(192, 168, 1, 1);    // Puerta de enlace
// IPAddress subnet(255, 255, 255, 0);   // Máscara de subred

// Página HTML con animación de colores
String HTML = "<!DOCTYPE html>\
<html lang=\"es\">\
<head>\
  <meta charset=\"UTF-8\">\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
  <title>Animación de Colores</title>\
  <style>\
    body {\
      font-family: Arial, sans-serif;\
      margin: 0;\
      padding: 0;\
      height: 100vh;\
      display: flex;\
      justify-content: center;\
      align-items: center;\
      text-align: center;\
      animation: colorChange 5s infinite;\
    }\
    h1 {\
      font-size: 3em;\
      color: #fff;\
      animation: textAnimation 3s ease-in-out infinite;\
    }\
    p {\
      font-size: 1.5em;\
      color: #fff;\
      animation: textFade 3s ease-in-out infinite;\
    }\
    @keyframes colorChange {\
      0% { background-color: #ff6347; }\
      25% { background-color: #4682b4; }\
      50% { background-color: #32cd32; }\
      75% { background-color: #ffd700; }\
      100% { background-color: #ff6347; }\
    }\
    @keyframes textAnimation {\
      0% { transform: translateY(-30px); opacity: 0; }\
      50% { transform: translateY(0); opacity: 1; }\
      100% { transform: translateY(30px); opacity: 0; }\
    }\
    @keyframes textFade {\
      0% { opacity: 0; }\
      50% { opacity: 1; }\
      100% { opacity: 0; }\
    }\
  </style>\
</head>\
<body>\
  <div>\
    <h1>¡Bienvenido a mi página!</h1>\
    <p>Este es un ejemplo de animación con cambios de color y textos en movimiento.</p>\
    <p>¡ESP32 está en acción!</p>\
  </div>\
</body>\
</html>";

// Función que maneja la ruta raíz (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Intentando conectar con WiFi...");
  
  WiFi.disconnect();  // Desconectar para evitar conflictos
  delay(100);
  
  // Configurar IP manual si es necesario (descomentar la línea en la parte superior)
  // WiFi.config(local_IP, gateway, subnet);

  WiFi.begin(ssid, password);  // Conectar a la red Wi-Fi
  int intentos = 0;

  while (WiFi.status() != WL_CONNECTED && intentos < 20) { // Máximo 20 intentos (~20 segundos)
    delay(1000);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.print("IP del ESP32: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_root);  // Configura la ruta principal
    server.begin();  // Inicia el servidor web

    Serial.println("Servidor HTTP iniciado");
  } else {
    Serial.println("\nNo se pudo conectar a WiFi. Reiniciando...");
    ESP.restart();  // Reinicia el ESP32 si no logra conectarse
  }
}

void loop() {
  server.handleClient();  // Maneja las solicitudes de los clientes
}
