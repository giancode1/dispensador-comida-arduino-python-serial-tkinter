//String SerialData="";
char SerialData;
int led =13;

void setup() {
  Serial.begin (9600); //inicia comunicacion serial
  pinMode(led,OUTPUT);
 
}

void loop() {

  if(Serial.available()>0){ //Verifica el primer caracter que ingresa al puerto serial
    //SerialData = Serial.readString();
    SerialData=Serial.read();

    Serial.print("I received: ");
    Serial.print(SerialData);


    if(SerialData=='1'){
      digitalWrite(led, HIGH);
      Serial.println("LED ON");
   }
    if(SerialData=='0'){
      digitalWrite(led, LOW);
      Serial.println("LED OFF");
   }
  }
}

   
