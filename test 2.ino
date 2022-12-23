// Konstanty pro režimy svícení
const int MODE_OFF = 0;
const int MODE_SOLID = 1;
const int MODE_BLINK = 2;
const int MODE_FADE = 3;
const int MODE_RANDOM = 4;
const int MODE_GRADIENT = 5;
const int MODE_CHASER = 6;
const int MODE_STROBE = 7;

// Globální proměnné pro uchování aktuálního stavu led pásku
int currentMode = MODE_SOLID;
int currentColor[3] = {255, 0, 0};

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
  currentMode = (currentMode + 1) % 8;
}

// Funkce pro náhodné přepínání mezi režimy svícení
void randomMode() {
  currentMode = random(8);
}

// Funkce pro zjištění aktuálního režimu svícení
int getMode() {
  return currentMode;
}

// Funkce pro vypnutí led pásku
void turnOff() {
  setColor(0, 0, 0);
}

// Funkce pro trvalé svícení v aktuální barvě
void solidLight() {
  setColor(currentColor[RED], currentColor[GREEN], currentColor[BLUE]);
}

// Funkce pro pulsní svícení v aktuální barvě
void blinkLight() {
  setColor(currentColor[RED], currentColor[GREEN], currentColor[BLUE]);
  delay(500);
  setColor(0, 0, 0);
  delay(500);
}

// Funkce pro postupné zesvětlování a zesvětlení v aktuální barvě
void fadeLight() {
  for (int i = 0; i < 256; i++) {
    setColor(i, i, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    setColor(i, i, i);
    delay(10);
  }
}

// Funkce pro režim "gradient": Led pásek běží přes celou škálu barev
void gradientLight() {
  for (int i = 0; i < 256; i++) {
    setColor(255, i, 0);
    delay(10);
  }
  for (int i = 0; i < 256; i++) {
    setColor(255-i, 255, 0);
    delay(10);
  }
  for (int i = 0; i < 256; i++) {
    setColor(0, 255, i);
    delay(10);
  }
  for (int i = 0; i < 256; i++) {
    setColor(0, 255-i, 255);
    delay(10);
  }
  for (int i = 0; i < 256; i++) {
    setColor(i, 0, 255);
    delay(10);
  }
  for (int i = 0; i < 256; i++) {
    setColor(255, 0, 255-i);
    delay(10);
  }
}

// Funkce pro náhodné přepínání mezi režimy svícení
void randomMode() {
  currentMode = random(8);
}

void loop() {
  switch (currentMode) {
    case MODE_OFF:
      turnOff();
      break;
    case MODE_SOLID:
      solidLight();
      break;
    case MODE_BLINK:
      blinkLight();
      break;
    case MODE_FADE:
      fadeLight();
      break;
    case MODE_RANDOM:
      randomMode();
      break;
    case MODE_GRADIENT:
      gradientLight();
      break;
    case MODE_CHASER:
      chaserLight();
      break;
    case MODE_STROBE:
      strobeLight();
      break;
  }
}
