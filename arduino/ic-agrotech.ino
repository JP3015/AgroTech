/*
Código IC-AGROTECH 
informações via serial no formato JSON para o servidor node-Red com dashboard

*/

/////Json
#include <ArduinoJson.h>
const int TAMANHO = 200;  //define o tamanho do buffer para o json

///// Sensor DTH
#include "DHT.h"
#define DHTPIN  7  //define o pino usado no arduino
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //declara a objeto da classe

/// Sensor humidade
#define SENSOR1  A0  //define o pino usado no arduino
#define SENSOR2  A1  //define o pino usado no arduino
#define SENSOR3  A2  //define o pino usado no arduino


/// Bomba D'agua
#define BOMBA1  8  //define o pino usado no arduino
#define BOMBA2  9  //define o pino usado no arduino
#define BOMBA3  10  //define o pino usado no arduino



////// Outras declarações
#define led 13 //define led conectado no pino 13
const int dry = 595;
const int wet = 239;

void setup() 
{
  //inicialia c sensor
  dht.begin();

  //inicializa comunicação serial
  Serial.begin(9600);

  //configura pinos de saida do arduinos
  pinMode(BOMBA1, OUTPUT);
  pinMode(BOMBA2, OUTPUT);
  pinMode(BOMBA3, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() 
{
  if (Serial.available() > 0) {
    //Lê o JSON disponível na porta serial:
    StaticJsonDocument<TAMANHO> json;
    deserializeJson(json, Serial);
    if(json.containsKey("bomba1")) {
      int valor = json["bomba1"];
      if(valor == 1){
        digitalWrite(BOMBA1, HIGH);
        delay(1000);
        //digitalWrite(BOMBA1,LOW);
      }else {
        digitalWrite(BOMBA1,LOW);      
      }
    }
    if(json.containsKey("bomba2")) {
      int valor = json["bomba2"];
      if(valor == 1){
        digitalWrite(BOMBA2, HIGH);
        delay(1000);
        //digitalWrite(BOMBA2,LOW);
      }else {
        digitalWrite(BOMBA2,LOW);      
      }
    }
    if(json.containsKey("bomba3")) {
      int valor = json["bomba3"];
      if(valor == 1){
        digitalWrite(BOMBA3, HIGH);
        delay(1000);
        //digitalWrite(BOMBA3,LOW);
      }else {
        digitalWrite(BOMBA3,LOW);      
      }
    }
    if(json.containsKey("led")) {
      int valor = json["led"];
      digitalWrite(led, valor);
    }
  } 
  
  StaticJsonDocument<TAMANHO> json; //Aloca buffer para objeto json

  // Faz a leitura da temperatura  
  float temp = dht.readTemperature();
  // faz a leitura da humidade
  float umi = dht.readHumidity();

  // Faz leitura do sensor solo 1
  int sensorVal1 = analogRead(SENSOR1);
  int umidade1 = map(sensorVal1,wet,dry,100,0);
  
// Faz leitura do sensor solo 2
  int sensorVal2 = analogRead(SENSOR2);
  int umidade2 = map(sensorVal2,wet,dry,100,0);

  // Faz leitura do sensor solo 1
  int sensorVal3 = analogRead(SENSOR3);
  int umidade3 = map(sensorVal3,wet,dry,100,0);
  
  //formato de escrita do json
  json["sTemp"] = temp;
  json["sUmi"] = umi;
  json["sensor1"] = umidade1;
  json["sensor2"] = umidade2;
  json["sensor3"] = umidade3;
  
  serializeJson(json, Serial);
  Serial.println();

  //delay
  delay(500);
}
