#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const unsigned long intervaloEnvio = 1000;  // Intervalo de tiempo entre envíos en milisegundos
unsigned long ultimoEnvio = 0;              // Tiempo del último envío
float datoflotante = 10.23;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Bienvenido");
  delay(1000);
  lcd.clear();
  
  Serial.begin(9600); // Inicializar la comunicación serial a 9600 baudios
}

void loop() {
  lcd.setCursor(0, 0);

  // Array para enviar
  String datostring = String(datoflotante, 2);
  
  //String enviarArray[] = {"lleno", "13.45", "1", "0"};
  String enviarArray[] = {"lleno", datostring, "1", "0"};

  // Verificar si ha pasado el intervalo de tiempo para enviar
  if (millis() - ultimoEnvio >= intervaloEnvio) {
    ultimoEnvio = millis(); // Actualizar el tiempo del último envío
    datoflotante = datoflotante +10.1;

    // Enviar el array
    for (int i = 0; i < 4; i++) {
      Serial.print(enviarArray[i]);
      Serial.print(",");
    }
    Serial.println(); // Enviar una nueva línea después del array
  }

  // Array para recibir
  String recibirArray[4];

  // Recibir el array
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');
    int index = 0;
    int commaIndex;
    while ((commaIndex = receivedData.indexOf(',')) != -1) {
      recibirArray[index] = receivedData.substring(0, commaIndex);
      receivedData = receivedData.substring(commaIndex + 1);
      index++;
    }
    recibirArray[index] = receivedData;

    // Imprimir el array recibido //solo para monitor serial
    for (int i = 0; i < 4; i++) {
      //Serial.print("Recibido: "); 
      Serial.println(recibirArray[i]);
      lcd.print(recibirArray[i]);
    }
    Serial.println();
    
  }
}
