#include <SIM800L.h>
#include <SoftwareSerial.h>

SoftwareSerial sim800(6, 7); // RX, TX
SIM800L gprs(sim800);

void setup() 
{
  Serial.begin(9600);
  sim800.begin(9600);

  while (!gprs.attachGPRS("APN", "username", "password")) {
    Serial.println("Failed to attach GPRS");
    delay(1000);
  }

  Serial.println("GPRS attached");
}

void loop() 
{
  // Send POST request with data
  String response = gprs.httpPOST("https://us-central1-londonwarddata.cloudfunctions.net/helloWorld/add", "{\"data\":\"55\"}", "Content-Type: application/json");

  // Print response
  Serial.println(response);

  // Delay between requests
  delay(1000);
}
