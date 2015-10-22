/*
 * IoT device for getting Price, posting Quantity changes. 
 */
     
#include <ESP8266WiFi.h>


const char* ssid      = "**** **** ****"; 
const char* password  = "**** **** ****"; 
const char* host      = "www.domain.com"; 
const int   httpPort  = 80; 


/* This device code is assigned as 'abcd1234' on the server. */
const char* price       = "/iotdemo/price/abcd1234/"; 
const char* upadd       = "/iotdemo/update/add/abcd1234/"; 
const char* upsub       = "/iotdemo/update/sub/abcd1234/"; 


void setup() 
{
    Serial.begin(9600); 
    delay(10); 
    
    WiFi.begin(ssid, password); 
    
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(1000); 
      Serial.print("."); 
    }
     
    Serial.println(""); 
    Serial.print("Wifi connected; IP address: "); 
    Serial.println(WiFi.localIP()); 
    
    pinMode(10, INPUT_PULLUP); 
    pinMode( 9, INPUT_PULLUP); 
}


int badd = 0; 
int bsub = 0; 


void loop() 
{
    WiFiClient client; 
    
    Serial.print("Getting Price: http://"); 
    Serial.print(host); 
    Serial.println(price); 
    
    if (!client.connect(host, httpPort)) 
    {
      Serial.println("Connection failed. ");
      return;
    }
    client.print(String("GET ") + price + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    delay(10); 
    
    while(client.available()) 
    {
      String dumpx = client.readStringUntil('{'); 
      String price = client.readStringUntil('}'); 
      Serial.println(price); 
    }
    Serial.println(); 


    /* Code for handling the buttons. */
    
    for (int i = 0; i < 100; i++)
    {
      badd = digitalRead(10); 
      bsub = digitalRead( 9); 
      
      if (badd == LOW)
      {
        Serial.println("Updating quantity:  PLUS"); 

        if (!client.connect(host, httpPort)) return; 
        client.print(String("GET ") + upadd + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(10); 

        while(client.available()) 
        {
          String dump1 = client.readStringUntil('{'); 
          String state = client.readStringUntil('}'); 
          Serial.println(state); 
        }
        Serial.println(); 
      }

      if (bsub == LOW)
      {
        Serial.println("Updating quantity: MINUS"); 
        
        if (!client.connect(host, httpPort)) return; 
        client.print(String("GET ") + upsub + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
        delay(10);

        while(client.available()) 
        {
          String dump2 = client.readStringUntil('{'); 
          String state = client.readStringUntil('}'); 
          Serial.println(state); 
        }
        Serial.println(); 
      }

      delay(100); 
    }
}

/* END OF FILE. */ 
