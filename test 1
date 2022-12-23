#include <Wire.h>
#include <ESP32.h>
#include <WiFi.h>
#include <WebServer.h>
#include <random.h>

// Konstanty pro definování režimů svícení
const int MODE_OFF = 0;
const int MODE_SOLID = 1;
const int MODE_BLINK = 2;
const int MODE_FADE = 3;

// Konstanty pro nastavení barvy led pásku
const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

// Proměnná pro uložení aktuálního režimu svícení
int currentMode = MODE_OFF;

// Proměnná pro uložení aktuální barvy led pásku
int currentColor[3] = {255, 255, 255};

// Funkce pro nastavení barvy led pásku
void setColor(int red, int green, int blue) {
  currentColor[RED] = red;
  currentColor[GREEN] = green;
  currentColor[BLUE] = blue;

  Wire.beginTransmission(8); // Adresa led pásku
  Wire.write(currentColor[RED]);
  Wire.write(currentColor[GREEN]);
  Wire.write(currentColor[BLUE]);
  Wire.endTransmission();
}

// Funkce pro nastavení aktuálního režimu svícení
void setMode(int mode) {
  currentMode = mode;
}

// Funkce pro přepínání mezi režimy svícení
void switchMode() {
  currentMode = (currentMode + 1) % 4;
}

// Funkce pro náhodné přepínání mezi režimy svícení
void randomMode() {
  currentMode = random(4);
}

// Funkce pro zjištění aktuálního režimu svícení
int getMode() {
  return currentMode;
}

// Funkce pro zjištění aktuální barvy led pásku
int* getColor() {
  return currentColor;
}

// Konfigurace WiFi
const char* ssid = "your_ssid";
const char* password = "your_password";

// Webový server pro ovládání led pásku
WebServer server(80);

void handleRoot() {
  // Zobrazení formuláře pro ovládání led pásku
  String form = "<form method='POST' action='/set'>"
                "  Režim svícení:<br>"
                "  <input type='radio' name='mode' value='0'> Vypnuto<br>"
                "  <input type='radio' name='mode' value='1'> Trvalé svícení<br>"
                "  <input type='radio' name='mode' value='2'> Pulsní svícení<br>"
                "  <input type='radio' name='mode' value='3'> Postupné zesvětlování a zesvětlení<br>"
                "  <input type='radio' name='mode' value='4' checked> Náhodné přepínání<br>"
                "  <br>"
                "  Barva:<br>"
                "  <input type='color' name='color'><br>"
                "  <br>"
                "  <input type='submit' value='Odeslat'>"
                "</form>";
  server.send(200, "text/html", form);
}

void handleSet() {
  // Získání dat z formuláře
  int mode = server.arg("mode").toInt();
  String colorStr = server.arg("color");
  int red = strtol( &colorStr[1], NULL, 16);
  int green = strtol( &colorStr[3], NULL, 16);
  int blue = strtol( &colorStr[5], NULL, 16);

  // Nastavení aktuálního režimu svícení a barvy led pásku
  setMode(mode);
  setColor(red, green, blue);

  // Zobrazení aktuálního nastavení
  String message = "Aktuální nastavení: režim svícení " + String(getMode()) + ", barva #" + colorStr;
  server.send(200, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Inicializace generatoru náhodných čísel
  randomSeed(analogRead(0));

  // Připojení k Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi připojeno");

  // Inicializace webového serveru
  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
  Serial.println("Webový server spuštěn");
}

void loop() {
  switch (currentMode) {
    case MODE_OFF:
      // Vypnutí led pásku
      setColor(0, 0, 0);
      break;
    case MODE_SOLID:
      // Trvalé svícení v aktuální barvě
      setColor(currentColor[RED], currentColor[GREEN], currentColor[BLUE]);
      break;
    case MODE_BLINK:
      // Pulsní svícení v aktuální barvě
      setColor(currentColor[RED], currentColor[GREEN], currentColor[BLUE]);
      delay(500);
      setColor(0, 0, 0);
      delay(500);
      break;
    case MODE_FADE:
      // Postupné zesvětlování a zesvětlení v aktuální barvě
      for (int i = 0; i < 256; i++) {
        setColor(i, i, i);
        delay(10);
      }
      for (int i = 255; i >= 0; i--) {
        setColor(i, i, i);
        delay(10);
      }
      break;
    case MODE_RANDOM:
      // Náhodné přepínání mezi režimy svícení
      randomMode();
      break;
  }

  // Obsluha požadavků na webovém serveru
  server.handleClient();
}


