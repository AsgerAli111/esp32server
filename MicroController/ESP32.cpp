#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";
AsyncWebServer server(80);

int pins[] = {13, 14, 18, 21, 22, 23, 25, 19};  // GPIO pins to control

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);  // Start with all pins OFF
  }

  // Handle requests to toggle individual pins
  server.on("/pin/<pin>/<state>", HTTP_GET, [](AsyncWebServerRequest *request) {
    String pinParam = request->pathArg(0);
    String stateParam = request->pathArg(1);
    int pin = pinParam.toInt();
    if (stateParam == "on") {
      digitalWrite(pin, HIGH);
      request->send(200, "text/plain", "Pin ON");
    } else {
      digitalWrite(pin, LOW);
      request->send(200, "text/plain", "Pin OFF");
    }
  });

  server.begin();
}

void loop() {
  // Nothing to do here, handled by the server
}
