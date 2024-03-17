#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "A54 milik Rian Syaputra";
const char* password = "12345678";
const int BUZZER_PIN = D5;
const int BTN_ONOFF = D1;
const int BTN_DOWN = D3;
const int BTN_UP = D2;
const int LED = D6;

int buzzer = 100;
int brightness = 3;


bool status = 0;



ESP8266WebServer server(80); // Port untuk web server

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_ONOFF, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // Halaman utama 
  server.begin(); // Memulai web server
}

void loop() {

    btnConfig();

    if (status) {
    analogWrite(LED, brightness);
    tone(BUZZER_PIN, buzzer);

  // Kondisi jika komponen off
  } else {
    analogWrite(LED, 0);
    noTone(BUZZER_PIN);
  }
  server.handleClient(); 
}


void handleRoot() {
  server.send(200, "text/html", "<html> <head> <meta http-equiv='refresh' content='5'> </head><body> <h1>BUZZER</h1><p> " + String(buzzer) + " <h1>LED</h1><p> " + String(brightness) + " </body></html>"); // Menampilkan halaman utama
}


void Upper() {
  if (status) {
    // buzzer += 10;
    // brightness += 3;
    if (buzzer <= 2500){
      buzzer += 10;
        //break;
       // buzzer = 2500;
        if (brightness <= 255){
        //break;
        brightness += 3;
        //brightness = 255;
        }
      }
      delay(100);
    }
}

void Lower() {
  if (status) {
    // buzzer -= 10;
    // brightness -= 3;
    delay(100);
    if (buzzer > 0){
        //break;
        buzzer -= 10;
        // buzzer = 0;
        if (brightness > 0){
        //break;
        brightness -= 3;
        // brightness = 0;
      }
    }
    delay(100);
  }
}


void btnConfig(){
   if (digitalRead(BTN_ONOFF) == LOW) {
    status = !status;
    delay(300);
  }

  if(digitalRead(BTN_UP) == LOW){
    Upper();
  }

  if(digitalRead(BTN_DOWN) == LOW){
    Lower();
  }

}