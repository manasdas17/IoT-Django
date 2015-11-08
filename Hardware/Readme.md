# Building the devices for the IoT-Demo 

This demo uses Wifi devices in the ESP8266 family, in particular the [NodeMCU](http://nodemcu.com/index_en.html). <br/> 
However it uses the Arduino IDE to compile programs rather than the built-in LUA interpreter. <br/> 
This [Adafruit guide](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide) would be helpful in setting up the Arduino IDE. <br/>

Each device is tagged as Cake.deviceid and the hardware consists of 1 NodeMCU board & 2 pull-up buttons. <br/>
A Serial-LCD (like [this model](https://www.sparkfun.com/products/9067) offered by Sparkfun) might also be helpful in displaying Cake.price. <br/> 
The TX pin (next to GND) will mirror all data sent over the USB port using the Arduino Serial interface.  
