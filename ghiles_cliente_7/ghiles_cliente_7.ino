#include <WiFi.h>

const char* ssid = "Nombre_Red_Servidor"; // Reemplaza con el SSID de tu red
const char* password = "Contraseña_Servidor"; // Reemplaza con la contraseña de tu red
const char* serverIP = "192.168.4.1"; // Reemplaza con la dirección IP del servidor
const int serverPort = 80;

void setup() {
  Serial.begin(115200);

  Serial.println("Conectándose a la red WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a la red WiFi. Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Simular dos valores enteros para enviar al servidor
  int value1 = 1; // Valor simulado 1 (número aleatorio entre 0 y 9)
  int value2 = 3; // Valor simulado 2 (número aleatorio entre 0 y 99)

  // Construir la solicitud al servidor en el formato "value1,value2"
  String request = String(value1) + "," + String(value2);

  Serial.print("Enviando solicitud al servidor: ");
  Serial.println(request);

  // Establecer la conexión con el servidor
  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    // Enviar la solicitud al servidor
    client.println(request);

    // Esperar la respuesta del servidor
    String response = client.readStringUntil('\r');
    Serial.print("Respuesta del servidor: ");
    Serial.println(response);
    
    // Si necesitas utilizar los valores de la respuesta separados por comas, puedes hacerlo de la siguiente manera:
    int serverValue1 = response.substring(0, response.indexOf(',')).toInt();
    response = response.substring(response.indexOf(',') + 1);
    int serverValue2 = response.substring(0, response.indexOf(',')).toInt();
    //response = response.substring(response.indexOf(',') + 1);
    //int serverValue3 = response.toInt();

    Serial.print("Valores recibidos del servidor: ");
    Serial.print(serverValue1);
    Serial.print(", ");
    Serial.print(serverValue2);
    //Serial.print(", ");
    //Serial.println(serverValue3);
  }
  
  // Esperar 5 segundos antes de enviar una nueva solicitud
  delay(5000);
}
