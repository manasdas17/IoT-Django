// ----------------------
// IoT Temperature Sensor
// ----------------------

int thermistor = A0; 
int led = D7; 
int analog; 


void setup() 
{
  Serial.begin(9600); 
  Spark.variable("temperature", &analog, INT);

  pinMode(led, OUTPUT); 
  pinMode(thermistor, INPUT); 
}


void loop() 
{
  digitalWrite(led, HIGH); 
  analog = analogRead(thermistor); 
  
  delay(2000); 
  Serial.println(analog); 
  
  digitalWrite(led, LOW); 
  analog = analogRead(thermistor); 
  
  delay(2000); 
  Serial.println(analog); 
}


/* END OF FILE. */ 
