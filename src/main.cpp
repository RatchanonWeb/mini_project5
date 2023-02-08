#include <Arduino.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "GET.h"
#define GREEN 33
#define RED 26
#define YELLOW 25
#define BUTTON 27
#define LDR 32
Bounce b = Bounce();
int id1 = 1;
int id2 = 1;
int id3 = 1;
int autost1 = 0;
int autost2 = 0;
int autost3 = 0;
int cnt = 0;
int res = 1000;
int timer = 0;
int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int status = 0;
int percent = 255;
TaskHandle_t TaskA = NULL;
TaskHandle_t TaskB = NULL;
TaskHandle_t TaskC = NULL;

void manual(void *param);

void GET(void *param);

void status_auto(void *param);

void Connect_Wifi()
{
  const char *ssid = "Galaxy A30C9C8";
  const char *password = "himl9080";
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}


void setup(){
    Serial.begin(115200);
    b.attach(BUTTON,INPUT_PULLUP);
    b.interval(25); 
    ledcSetup(0, 5000, 8);
    ledcAttachPin(RED, 0);
    ledcSetup(1, 5000, 8);
    ledcAttachPin(YELLOW, 1);
    ledcSetup(2, 5000, 8);
    ledcAttachPin(GREEN, 2);
    b.attach(BUTTON, INPUT_PULLUP);
    b.interval(25); 
    Connect_Wifi();
    xTaskCreatePinnedToCore(GET, "GET_VALUE", 50000, NULL, 2, &TaskA, 1);
    xTaskCreatePinnedToCore(status_auto, "AUTO_LED", 50000, NULL, 1, &TaskB, 0);
    xTaskCreatePinnedToCore(manual, "MANUAL_LED", 50000, NULL, 1, &TaskC, 1);
      
}

void loop(){
}

void manual(void *param) {
  while(1) {
    if(autost1 == 0) {

      if(touchRead(2) <=11){
        if(ch1==0){
          ledcWrite(0, percent);
          ch1 = 1;
        }
        else{
          ledcWrite(0, 0);
          ch1 = 0;
        }
      }
      
      if(GET_value(1) == 1)  {
        ledcWrite(0, percent);
        ch1 = 1;
      } else {
        ledcWrite(0, 0);
        ch1 = 0;
      }
    }
    if(autost2 == 0) {
      if(touchRead(12) <=11){
        if(ch2==0){
          ledcWrite(1, percent);
          ch2 = 1;
        }
        else{
          ledcWrite(1, 0);
          ch2 = 0;
        }
      }

      if(GET_value(2) == 1)  {
        ledcWrite(1, percent);
        ch2 = 1;
      } else {
        ledcWrite(1, 0);
        ch2 = 0;
      }
    }
    if(autost3 == 0) {
      if(touchRead(13) <=13){
        if(ch3==0){
          ledcWrite(2, percent);
          ch3 = 1;
        }
        else{
          ledcWrite(2, 0);
          ch3 = 0;
        }
      }

      if(GET_value(3) == 1)  {
        ledcWrite(2, percent);
        ch3 = 1;
      } else {
        ledcWrite(2, 0);
        ch3 = 0;
      }

    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void GET(void *param){
    while(1){
      autost1=GET_auto(1);
      autost2=GET_auto(2);
      autost3=GET_auto(3);
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void status_auto(void *param){
    while(1){
      if(autost1 == 1) {
        //percent = GETPERC();
        percent = 255;
        int bright = map(analogRead(LDR),300,4095,0,255);
        //Serial.print("this is brightness: ");
        //Serial.println(bright);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(bright < 150) { // มืด
          ledcWrite(0, 0);
        } else {
          ledcWrite(0, percent);
        }
        vTaskDelay(5/portTICK_PERIOD_MS);
      }
      if(autost2 == 1) {
        //percent = GETPERC();
        percent = 255;
        int bright = map(analogRead(LDR),300,4095,0,255);
        //Serial.print("this is brightness: ");
        //Serial.println(bright);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(bright < 150) { // มืด
          ledcWrite(1, 0);
        } else {
          ledcWrite(1, percent);
        }
        vTaskDelay(5/portTICK_PERIOD_MS);
      }
      if(autost3 == 1) {
        //percent = GETPERC();
        percent = 255;
        int bright = map(analogRead(LDR),300,4095,0,255);
        //Serial.print("this is brightness: ");
        //Serial.println(bright);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(bright < 150) { // มืด
          ledcWrite(2, 0);
        } else {
          ledcWrite(2, percent);
        }
        vTaskDelay(5/portTICK_PERIOD_MS);
      }
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
}