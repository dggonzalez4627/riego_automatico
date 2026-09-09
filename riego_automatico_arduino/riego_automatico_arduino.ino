#include <LiquidCrystal.h>

// Proyecto: Riego automatico con Arduino UNO
// LCD 16x2 paralelo, potenciometro/sensor en A0, rele en D8 y pulsador en D7.

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const int relePin = 8;
const int botonPin = 7;

// Umbrales de control automatico
const int humedadEncenderBomba = 35;
const int humedadApagarBomba = 55;

// true para modulos de rele activos en LOW.
// Si tu rele enciende con HIGH, cambia este valor a false.
const bool releActivoEnBajo = true;

bool bombaEncendida = false;
bool bombaAuto = false;
bool bombaManualFija = false;
bool botonMantenido = false;

bool ultimoEstadoBoton = HIGH;
bool estadoBotonEstable = HIGH;

unsigned long ultimoCambioBoton = 0;
unsigned long ultimoClick = 0;

const unsigned long tiempoRebote = 50;
const unsigned long tiempoDobleClick = 400;

int leerHumedad(int lectura) {
  // Con potenciometro:
  // 0 = 0%, 1023 = 100%
  int humedad = map(lectura, 0, 1023, 0, 100);
  humedad = constrain(humedad, 0, 100);
  return humedad;
}

void controlarRele(bool encender) {
  bombaEncendida = encender;

  if (releActivoEnBajo) {
    digitalWrite(relePin, encender ? LOW : HIGH);
  } else {
    digitalWrite(relePin, encender ? HIGH : LOW);
  }
}

void evaluarHumedad(int humedad) {
  if (humedad <= humedadEncenderBomba) {
    bombaAuto = true;
  }

  if (humedad >= humedadApagarBomba) {
    bombaAuto = false;
  }
}

void leerBoton() {
  bool lectura = digitalRead(botonPin);

  if (lectura != ultimoEstadoBoton) {
    ultimoCambioBoton = millis();
    ultimoEstadoBoton = lectura;
  }

  if ((millis() - ultimoCambioBoton) > tiempoRebote) {
    if (lectura != estadoBotonEstable) {
      estadoBotonEstable = lectura;

      if (estadoBotonEstable == LOW) {
        botonMantenido = true;

        unsigned long ahora = millis();

        if (ahora - ultimoClick <= tiempoDobleClick) {
          bombaManualFija = !bombaManualFija;
          ultimoClick = 0;
        } else {
          ultimoClick = ahora;
        }
      }

      if (estadoBotonEstable == HIGH) {
        botonMantenido = false;
      }
    }
  }
}

void actualizarBomba() {
  bool encender = bombaAuto || botonMantenido || bombaManualFija;
  controlarRele(encender);
}

void mostrarLCD(int humedad) {
  lcd.setCursor(0, 0);
  lcd.print("Humedad ");
  lcd.print(humedad);
  lcd.print("% RH   ");

  lcd.setCursor(0, 1);

  if (bombaManualFija) {
    lcd.print("Bomba: FIJA ON ");
  } else if (botonMantenido) {
    lcd.print("Bomba: MANUAL  ");
  } else if (bombaAuto) {
    lcd.print("Bomba: AUTO ON ");
  } else {
    lcd.print("Bomba: OFF     ");
  }
}

void imprimirSerial(int lectura, int humedad) {
  Serial.print("A0: ");
  Serial.print(lectura);
  Serial.print(" | Humedad: ");
  Serial.print(humedad);
  Serial.print("% RH");
  Serial.print(" | Auto: ");
  Serial.print(bombaAuto ? "ON" : "OFF");
  Serial.print(" | Manual fijo: ");
  Serial.print(bombaManualFija ? "ON" : "OFF");
  Serial.print(" | Boton: ");
  Serial.print(botonMantenido ? "PRESIONADO" : "SUELTO");
  Serial.print(" | Rele: ");
  Serial.println(bombaEncendida ? "ON" : "OFF");
}

void setup() {
  Serial.begin(9600);

  pinMode(relePin, OUTPUT);
  pinMode(botonPin, INPUT_PULLUP);

  controlarRele(false);

  lcd.begin(16, 2);
  delay(100);

  lcd.clear();
  lcd.print("Riego automatico");
  lcd.setCursor(0, 1);
  lcd.print("Sistema listo");
  delay(1500);
  lcd.clear();

  Serial.println("Sistema iniciado");
}

void loop() {
  int lectura = analogRead(sensorPin);
  int humedad = leerHumedad(lectura);

  leerBoton();
  evaluarHumedad(humedad);
  actualizarBomba();

  mostrarLCD(humedad);
  imprimirSerial(lectura, humedad);

  delay(100);
}
