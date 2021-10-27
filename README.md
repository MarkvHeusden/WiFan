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

## Step 1: Connecting the Relay
Connect your Microcontroller to your computer via USB. Then take your relay and connect it to your Microcontroller. My relay looked something like this:

<img src="img/IMG_4098.jpeg" alt="Relay" width="500"/>
<img src="img/IMG_4097.jpeg" alt="Relay" width="500"/>

As you can see my relay has 4 pins: GND, VCC, NC and SIG. For this case, I'm only using GND, VCC and SIG. The white cable (NC) remains unplugged. I found [this awesome guide](https://diyi0t.com/relay-tutorial-for-arduino-and-esp8266/) on connecting a relay to a Microcontroller. The guide includes the following illustration, showing you how to connect every wire:

<img src="img/Relais-Module-NodeMCU_Steckplatine.png" alt="how to cennect relay to esp8266" width="500"/>

Connect the black wire (GND) with the Ground pin on my ESP8266 and connect the red wire (VCC) with the 3V3 pin on your board. Leave the white wire unplugged and connect the yellow wire (SIG) with D7 pin on your board.

> Warning! Connect these wires carefully. The guide I used and the picture above told me to connect the VCC on the relay with the VIN pin on your board when using an ESP8266 or ESP32, because you need a 5V output. I’ve tried it, and my wire immediately started smoking, so please don’t make the same mistake. The 3V3 pin works fine for me instead.

With everything connected, your board should look something like this:

<img src="img/IMG_4102.jpeg" alt="esp8266 connected" width="500"/>


After connecting the wires it is time to test our relay. I used the following code:

````c++
int relay = D7;

void setup() {
  pinMode(relay, OUTPUT);
}

void loop() {
  digitalWrite(relay, HIGH);
  delay(2000);
  digitalWrite(relay, LOW);
  delay(2000);
}
````
This simple program start by turning on the relay. 2 seconds after that, it turns off. 2 seconds later, the loop function starts again. This is a simple way to test if everything is working so far.

Did everything work as planned? Congrats! 🥳 Let's move onto the next step.

## Step 2: Connecting a power cable
A relay is a low-power electrical switch which toggles on and off a high-power (Max 250V) circuit. For this reason we need to connect the relay to the power cable of the object we want to switch. In this case it's a fan. Because I didn't want to ruin my fans power cable, and I might want to switch different higher voltage objects in the future, I decided to use an old extension cord. If you're like me and you don't have experience cutting and stripping wires, I reccomend using an extension cord with a switch. With this extension cord, u can just remove the switch to reveal the wires.

<img src="img/IMG_4131.jpeg" alt="esp8266 connected" width="500"/>

My extension cord looked something like this. As you can see it has a switch, which makes it easy for me to connect the relay. You do need to use a terminal block however with this cord, because both wires will be exposed when you remove the switch and you only need 1 for the relay. After removing the switch or cutting open the cable and revealing/stripping the wires, your extension cord should look something like this:

<img src="img/IMG_4134.jpeg" alt="esp8266 connected" width="500"/>

> As you can see in the picture my extension cord is an ungrounded cable. This might make it a bit easier to connect, but you can't connect every device to this extension cord, because most bigger devices have grounded plugs. I found this out too late which prevented me from connecting the fan I wanted to connect.

Now you can connect your relay to one of the two cables. Just put both stripped ends of 1 wire in your relay and screw it down. Put a terminal block on the other cable to continue the circuit. After you've finished connecting the relay, it should look something like this:

<img src="img/IMG_4131.jpeg" alt="esp8266 connected" width="500"/>




## api
And now for the fun part
