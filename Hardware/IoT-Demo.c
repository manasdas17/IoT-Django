/* IoT device for getting Price, posting Quantity changes. */

#include <ESP8266WiFi.h> 

const char* ssid      = "**** **** ****"; 
const char* password  = "**** **** ****"; 
const char* host      = "www.domain.com"; 
const int   httpPort  = 80; 

/* This device code is assigned as 'abcd1234' on the server. */ 
const char* price     = "/iotdemo/price/abcd1234/"; 
const char* upadd     = "/iotdemo/update/add/abcd1234/"; 
const char* upsub     = "/iotdemo/update/sub/abcd1234/"; 

int badd = 0; 
int bsub = 0; 


void setup() 
{
    Serial.begin(9600); delay(200); 
    
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(1000); Serial.print("."); 
    }
    ClearScreen(); 
    Serial.println(" Wifi connected. "); delay(2000); 
    
    pinMode(10, INPUT_PULLUP); 
    pinMode( 9, INPUT_PULLUP); 
}

void loop() 
{
    WiFiClient client; 
    ClearScreen(); 
    
    if (!client.connect(host, httpPort)) 
    {
      Serial.print(" FAILED! "); 
      return;
    }
    client.print(String("GET ") + price + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
    
    Serial.print(" Price: "); delay(10); 
    while (client.available()) 
    {
      String dumpx = client.readStringUntil('{'); 
      String price = client.readStringUntil('}'); 
      Serial.print(price); 
    }

    /* Code for handling the buttons. */
    for (int i = 0; i < 100; i++)
    {
      badd = digitalRead(10); 
      bsub = digitalRead( 9); 
      
      if (badd == LOW)
      {
        Serial.println(" Updating: + "); 
        if (!client.connect(host, httpPort)) return; 
        client.print(String("GET ") + upadd + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(10); 

        while(client.available()) 
        {
          String dump1 = client.readStringUntil('{'); 
          String state = client.readStringUntil('}'); 
          Serial.print(state); 
        }
      }
      if (bsub == LOW)
      {
        Serial.println(" Updating: - "); 
        if (!client.connect(host, httpPort)) return; 
        client.print(String("GET ") + upsub + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(10);

        while(client.available()) 
        {
          String dump2 = client.readStringUntil('{'); 
          String state = client.readStringUntil('}'); 
          Serial.print(state); 
        }
      }
      delay(100); 
    }
}

void ClearScreen()
{
    Serial.write(254); Serial.write(128); 
    Serial.write("                "); Serial.write("                "); 
    Serial.write(254); Serial.write(128); 
}

/* END OF FILE. */ 
