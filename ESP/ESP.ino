// подключаем библиотеку «ESP8266WiFi»:
#include <ESP8266WiFi.h>

// вписываем здесь SSID и пароль для WiFi-сети:
const char* ssid = "iPhone";
const char* password = "czternascie";

// веб-сервер на порте 80:
WiFiServer server(80);

// блок setup() запускается только один раз – при загрузке:
void setup() {
  // инициализируем последовательный порт (для отладки):
  Serial.begin(115200);
  delay(10);
  //светодиод будет светиться пока плата не найдет заданную сеть
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  
  // подключаемся к WiFi-сети:
  Serial.println();
  Serial.print("Connecting to "); // "Подключаемся к "
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(0, LOW);    //выключаем светодиолд
  
  Serial.println("");
  Serial.println("WiFi connected"); // "Подключение к WiFi выполнено"

  // запускаем веб-сервер:
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  // "Веб-сервер запущен. Ожидание IP-адреса ESP..."
  delay(10000);

  // печатаем IP-адрес ESP:
  Serial.println(WiFi.localIP());
}

// блок loop() будет запускаться снова и снова:
void loop() {
  // начинаем прослушку входящих клиентов:
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");  //  "Новый клиент"
    // создаем переменную типа «boolean»,
    // чтобы определить конец HTTP-запроса:
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && blank_line) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // веб-страница с данными о температуре:
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>ESP8266 - Temperature</h1><h3>Temperature in Celsius: ");
          client.println("done)))");
          client.println("*C</h3><h3>Temperature in Fahrenheit: ");
          client.println("*F</h3></body></html>");
          break;
        }
        if (c == '\n') {
          // если обнаружен переход на новую строку:
          blank_line = true;
        }
        else if (c != '\r') {
          // если в текущей строчке найден символ:
          blank_line = false;
        }
      }
    }
    // закрываем соединение с клиентом:
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
    //  "Клиент отключен."
  }
}
