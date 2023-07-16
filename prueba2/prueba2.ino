#include <TimeLib.h>

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const unsigned long time_ms = 1000;  // Intervalo de tiempo entre envíos en milisegundos
unsigned long start = 0;              
float datoflotante = 10.23;

//hora:
int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;

//puerta alta
String puerta_alta = "0";

//puerta baja
String puerta_baja = "0";

// Array recibido
String arrayRecibido[4];

//puerta baja tiempo abierta:
unsigned long tiempoInicioPuertaBaja = 0;
const unsigned long tiempoPuertaBajaAbierta = 3000;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Bienvenido");
  delay(500);
  
  lcd.clear();
  
  Serial.begin(9600); // Inicializar la comunicación serial a 9600 baudios
  setTime(17, 30, 0, 18, 7, 2023);  // Hora: 17:30:00, Fecha: 18/07/2023
}

void loop() {

  //hora de la comida:
  if(hour() == 12 && minute() == 00 && second() == 10){
    puerta_baja = "1";
    digitalWrite(8, HIGH);  //abrir puerta_baja
    if(tiempoInicioPuertaBaja==0){
      tiempoInicioPuertaBaja = millis();
    }
    
  }

  //hora de la comida:
  if(hour() == 15 && minute() == 00 && second() == 10){
    puerta_baja = "1";
    digitalWrite(8, HIGH);  //abrir puerta_baja
    if(tiempoInicioPuertaBaja==0){
      tiempoInicioPuertaBaja = millis();
    }
  }

  // Cerrar puerta baja despues de 3 segundos desde que se abrio
  if(tiempoInicioPuertaBaja !=0 && millis() - tiempoInicioPuertaBaja >= tiempoPuertaBajaAbierta){
    digitalWrite(8, LOW); //cerrar puerta_baja
    tiempoInicioPuertaBaja=0;
    puerta_baja = "0";
  }
  
  // Array para enviar
  String datostring = String(datoflotante, 2);
  String arrayEnviado[] = {"lleno", datostring, puerta_alta, puerta_baja};

  if (millis() > start + time_ms) {
    start = millis();
    mihora();
    datoflotante = datoflotante +10.1;

    // Enviar el array
    int longitudArrayEnviado = sizeof(arrayEnviado) / sizeof(arrayEnviado[0]); // Obtener la longitud del array
    for (int i = 0; i < longitudArrayEnviado; i++) {
      Serial.print(arrayEnviado[i]);
      Serial.print(",");
    }
    Serial.println(); // Enviar una nueva línea después del array
  }


  if (Serial.available()>0) {
    lcd.setCursor(0, 0);  // Establecer el cursor en la posición (0, 0)
    lcd.print("                ");  // Imprimir una cadena vacía de 16 caracteres
    
    // Recibir el array
    String receivedData = Serial.readStringUntil('\n');
    int index = 0;
    int commaIndex;
    while ((commaIndex = receivedData.indexOf(',')) != -1) {
      arrayRecibido[index] = receivedData.substring(0, commaIndex);
      receivedData = receivedData.substring(commaIndex + 1);
      index++;
    }
    arrayRecibido[index] = receivedData;
    
    String newTime = arrayRecibido[0]; //tiempo que viene de serial-python
    if( newTime.length() == 8 ){
      setTime(newTime.substring(0,2).toInt(), newTime.substring(3,5).toInt(), newTime.substring(6,8).toInt() ,day(), month(), year());
    }

    //PUERTA ALTA
    if(arrayRecibido[1]=="1"){
      digitalWrite(13, HIGH);
      puerta_alta="1";
    }
    if(arrayRecibido[1]=="0"){
      digitalWrite(13, LOW);
      puerta_alta="0";
    }

    //PUERTA BAJA
    if(arrayRecibido[2]=="1"){
      digitalWrite(8, HIGH);
      puerta_baja="1";
    }
    if(arrayRecibido[2]=="0"){
      digitalWrite(8, LOW);
      puerta_baja="0";
    }

    // Imprimir el array recibido en lcd
    lcd.setCursor(0, 0);
    int longitudArrayRecibido = sizeof(arrayRecibido) / sizeof(arrayRecibido[0]); // Obtener la longitud del array
    
    for (int i = 0; i < longitudArrayRecibido; i++) {
      lcd.print(arrayRecibido[i]);
    }

    
  }
}

void mihora(){
  //time_t currentTime = now();
  currentHour = hour();
  currentMinute = minute();
  currentSecond = second();

  // Mostrar la hora en el LCD
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.print("Hora:");
  lcd.setCursor(0, 1);
  lcd.print(currentHour);
  lcd.print(":");
  lcd.print(currentMinute);
  lcd.print(":");
  lcd.print(currentSecond);
  lcd.setCursor(0, 0);
}
