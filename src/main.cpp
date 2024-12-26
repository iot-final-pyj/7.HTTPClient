#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

const char* ssid = "IoT518";
const char* password = "iot123456";

WiFiClient client;

void setup(void){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to "); Serial.println(ssid);
    Serial.print("IP address: "); Serial.println(WiFi.localIP());

    MDNS.begin("miniwifi");
}

void loop(void){
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://vulnweb.com/")) {  // HTTP

        Serial.print("[HTTP] GET...\n");  // start connection and send HTTP header
        int httpCode = http.GET();

        if (httpCode > 0) {                // httpCode will be negative on error
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
        Serial.printf("[HTTP} Unable to connect\n");
    }

    delay(10000);
}
