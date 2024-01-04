#include <WiFi.h>

const char* ssid = "Nombre_Red_Servidor";
const char* password = "Contraseña_Servidor";
WiFiServer server(80);

int buttonPin = 5;
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  // Configurar el ESP32 como un punto de acceso
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
  Serial.println("Server started");
}

void loop() {

  WiFiClient client = server.available();

  if (client) {
    //Serial.println("New client connected");
    while (client.connected()) {
      // Leer el estado del botón
      buttonState = 99;

      //String response = String(buttonState) + "," + String(analogRead(A0)) + "," + String(random(100));
      //client.println(response);

      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.print("Client says: ");
        Serial.print(request);
        Serial.print(", ");

        int b = request.length();
        //Serial.print("b=");
        //Serial.println(b);

        if (b > 2) {
          int value1 = request.substring(0, request.indexOf(',')).toInt();
          request = request.substring(request.indexOf(',') + 1);
          int value2 = request.toInt();
          Serial.print("Received values from client: ");
          Serial.print(value1);
          Serial.print(", ");
          Serial.println(value2);
        }

      }


      //////// cada 3 segundos envia
      static unsigned long a;
      if (millis() > a + 5000) {
        a = millis();
        // Enviar dos variables simuladas al servidor
        int value1 = 2; // Valor simulado 1
        int value2 = 4; // Valor simulado 2
        int value3 = 6; // Valor simulado 2
          String response = String(value1) + "," + String(value2)+ "," + String(value3);
        //String response = String(buttonState) + "," + String(analogRead(A0)) + "," + String(random(100));

        Serial.print("Sending response: ");
        Serial.println(response);

        client.println(response);

        client.stop();

      }

    }
    //Serial.println("Client disconnected");
  }
}
