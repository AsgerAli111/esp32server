#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "nopassword";
const char* password = "password11";
const char* secondaryEspIP = "192.168.1.100";

WebServer server(80);

const int primaryGpioPins[] = {2, 4, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  for (int i = 0; i < sizeof(primaryGpioPins) / sizeof(primaryGpioPins[0]); i++) {
    pinMode(primaryGpioPins[i], OUTPUT);
    digitalWrite(primaryGpioPins[i], LOW);
  }

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/toggle_secondary", handleToggleSecondary);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  String html = "<html><head><style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; }";
  html += ".container { max-width: 500px; margin: auto; padding: 20px; background-color: white; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1); }";
  html += "h1 { text-align: center; color: #333; }";
  html += ".btn { display: block; width: 100%; padding: 10px; margin: 10px 0; text-align: center; color: white; background-color: #007BFF; border: none; border-radius: 5px; text-decoration: none; font-size: 16px; }";
  html += ".btn:hover { background-color: #0056b3; }";
  html += "</style></head><body>";
  html += "<div class='container'><h1>ESP32 GPIO Control</h1>";

  html += "<h2>Primary ESP32 GPIOs</h2>";
  for (int i = 0; i < sizeof(primaryGpioPins) / sizeof(primaryGpioPins[0]); i++) {
    html += "<a class='btn' href='/toggle?pin=" + String(primaryGpioPins[i]) + "'>Toggle GPIO " + String(primaryGpioPins[i]) + "</a>";
  }

  html += "<h2>Secondary ESP32 GPIOs</h2>";
  for (int i = 0; i < sizeof(primaryGpioPins) / sizeof(primaryGpioPins[0]); i++) {
    html += "<a class='btn' href='/toggle_secondary?pin=" + String(primaryGpioPins[i]) + "'>Toggle GPIO " + String(primaryGpioPins[i]) + "</a>";
  }

  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  if (server.hasArg("pin")) {
    int pin = server.arg("pin").toInt();
    if (digitalRead(pin) == LOW) {
      digitalWrite(pin, HIGH);
    } else {
      digitalWrite(pin, LOW);
    }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleToggleSecondary() {
  if (server.hasArg("pin")) {
    int pin = server.arg("pin").toInt();
    HTTPClient http;
    String url = "http://" + String(secondaryEspIP) + "/toggle?pin=" + String(pin);
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.println("Secondary ESP32 Pin Toggled");
    } else {
      Serial.println("Error on toggling Secondary ESP32 Pin");
    }
    http.end();
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void loop() {
  server.handleClient();
}
