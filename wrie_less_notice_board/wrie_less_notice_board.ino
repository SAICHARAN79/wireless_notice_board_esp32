//Include required libraries
#include "WiFi.h"
#include <HTTPClient.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
// WiFi credentials
const char* ssid = "sai";         // change SSID
const char* password = "sai1234sai";    // change password
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycbxGGf7j0aUn_RdNyNFbEirqXtk0KNwQ1QiBHry3IzAkYEgIyLEuY6U5LzN4n8VprT62";    // change Gscript
void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0,0);  
 lcd.print(" ESP32    "); 
 lcd.setCursor (0,1);  
 lcd.print(" WIRELESS NOTICE BOARD ");  
 delay (2000);  
 lcd.clear();   
  Serial.begin(115200);
  delay(1000);
  // connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?read";
    Serial.println("Making a request");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    String payload;
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      lcd.setCursor (0, 1);
      lcd.print(payload);
    }
    else {
      Serial.println("Error on HTTP request");
      lcd.setCursor(0,2);
      lcd.print("Error on HTTP request");
    }
    http.end();
  }
  delay(1000);
}
