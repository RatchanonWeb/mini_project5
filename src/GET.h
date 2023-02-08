#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>
int x;
const String baseUrl = "https://ecourse.cpe.ku.ac.th/exceed05/hard/get_status";

int GET_value(int id)
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);
    id = id-1;
    Serial.println((const int)doc["result"][id]["is_it_open"]);
    return doc["result"][id]["is_it_open"];
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }
}

int GET_auto(int id)
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);

    //Serial.println((const int)doc["result"][0]["is_it_open"]);
    id = id-1;
    return doc["result"]["percent"];
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }
}

int GET_per()
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);

    //Serial.println((const int)doc["result"][0]["is_it_open"]);
    //return doc["result"][id]["is_auto_or_manual"];
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }
}
/*
void POST_post(){
    String json;
    DynamicJsonDocument doc(65536);
    doc["userId"] = 1;
    doc["title"] = "Exceed AHHHHHH";
    doc["body"] = "THIS IS BODY";
    serializeJson(doc,json);

    const String url = baseUrl + "posts";
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type","application/json");

    int httpResponseCode = http.POST(json);
    if (httpResponseCode >= 200 && httpResponseCode < 300) {
        Serial.print("HTTP ");
        Serial.println(httpResponseCode);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
}
*/