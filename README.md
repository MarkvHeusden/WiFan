# 💨 WiFan 

This manual is made for an IoT schoolproject. I've created an IoT fan called WiFan. You can controll the fan using an app, a voice assistant, or you can connect it to a weather API to turn on when the temperature rises. In this manual I will show you how I connected my fan to an open weather API using a NodeMCU ESP8266.

![banner](img/Bannner.png)

The manual will be divided into 4 main sections. ???????????????????
1. Setting up the Microcontroller & Relay ??? hardware eerst
2. Connecting the Microcontroller & Relay to your fan
3. Using an open weather API to get your outside temperature
4. Putting everything together to make a working product

## Prerequisites
When following this manual I assume that you have the following hardware & software installed. If this is not the case, please set-up your Microcontroller correctly before following this manual.

### Hardware
* NodeMCU ESP8266 Microcontroller (or similar board)
* Relay Module
* Extension Cord (optional but preferable)
* Fan

### Software
* [Arduino IDE](https://www.arduino.cc/en/software)
* NodeMCU USB Drivers

### Libaries?
* ArduinoJson?
* ArduinoHttpClient?
* ESP8266WiFi
* ESP8266HTTPClient

## Step 1: Connecting the hardware
Connect your Microcontroller to your computer via USB. Then take your relay and connect it to your Microcontroller. My relay looked something like this:

<img src="img/IMG_4098.jpeg" alt="Relay" width="800"/>
<img src="img/IMG_4097.jpeg" alt="Relay" width="800"/>

As you can see my relay has 4 pins: GND, VCC, NC and SIG. For this case, I'm only using GND, VCC and SIG. The white cable (NC) remains unplugged. I found [this awesome guide](https://diyi0t.com/relay-tutorial-for-arduino-and-esp8266/) on connecting a relay to a Microcontroller. The guide includes the following illustration, showing you how to connect every wire:

<img src="img/Relais-Module-NodeMCU_Steckplatine.png" alt="how to cennect relay to esp8266" width="800"/>

Connect the black wire (GND) with the Ground pin on my ESP8266 and connect the red wire (VCC) with the 3V3 pin on your board. Leave the white wire unplugged and connect the yellow wire (SIG) with D7 pin on your board.

> Warning! Connect these wires carefully. The guide I used and the picture above told me to connect the VCC on the relay with the VIN pin on your board when using an ESP8266 or ESP32, because you need a 5V output. I’ve tried it, and my wire immediately started smoking, so please don’t make the same mistake. The 3V3 pin works fine for me instead.

With everything connected, your board should look something like this:

<img src="img/IMG_4102.jpeg" alt="esp8266 connected" width="800"/>


After connecting the wires it is time to test our relay. I used the following code:


## api
And now for the fun part
