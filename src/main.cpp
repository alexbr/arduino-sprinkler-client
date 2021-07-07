/********************************************************

  Alex's sprinkler control

 *********************************************************/

#include "main.h"
#include "secrets.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiClient.h>
#include <Wire.h>

// Internet setup
IPAddress gatewayIP(192, 168, 10, 1);
WiFiClient client;
const char* sprinklerReceiver = RECEIVER_URL;

unsigned long checkTriggerTime = 0;

void setup() {
   Serial.begin(9600);
   pinMode(TRIGGER_PIN_IN, INPUT);
   connect();
}

void loop() {
   if (WiFi.status() != WL_CONNECTED) {
      connect();
   }

   if (millis() > checkTriggerTime) {
      checkTrigger();
      checkTriggerTime = millis() + 1000;
   }
}

bool connect() {
   const char *ssid = SECRET_SSID;
   const char *passkey = SECRET_PASSKEY;

   bool connected = false;
   while (!connected) {
      Serial.println("Disconnecting WiFi");
      WiFi.disconnect();
      
      Serial.print("Connecting WiFi");
      WiFi.begin(ssid, passkey);

      unsigned long waitUntil = millis() + 60000;
      
      while (!connected && millis() < waitUntil) {
         connected = WiFi.status() == WL_CONNECTED;
         Serial.print(WiFi.status());
         Serial.print(",");
         Serial.print(WiFi.reasonCode());
         Serial.print(".");
         delay(500);
      }
   }
   
   Serial.println("");
   Serial.println(WiFi.localIP());

   WiFi.noLowPowerMode();
   return connected;
}

void checkTrigger() {
   while (client.available()) {
      Serial.write(client.read());
   }
   
   client.stop();
   if (digitalRead(TRIGGER_PIN_IN) == HIGH) {
      printStringLn("sprinkler zone on");
      if (WiFi.ping(sprinklerReceiver) >= 0 && client.connect(sprinklerReceiver, 80)) {
         client.println("GET /on HTTP/1.1");
         client.println("Connection: close");
         client.println();
      }
   } else {
      printStringLn("sprinkler zone off");
      if (WiFi.ping(sprinklerReceiver) >= 0 && client.connect(sprinklerReceiver, 80)) {
         client.println("GET /off HTTP/1.1");
         client.println("Connection: close");
         client.println();
      }
   }
}

void printString(const char *str) {
   const char *p = str;
   while (*p) {
      Serial.print(*p);
      p++;
   }
}

void printStringLn(const char *str) {
   printString(str);
   Serial.print('\n');
}

void printStringP(const char *str) {
   char c[strlen_P(str) + 1];
   strcpy_P(c, str);
   printString(c);
}

void printStringLnP(const char *str) {
   printStringP(str);
   Serial.print('\n');
}