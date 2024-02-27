
# Inav sPortMaster feature use 
Documentation and Arduino code for use the [Inav](https://github.com/iNavFlight/inav) "SmartPort Master" feature

## Table of contents
* [Description](#description)
* [HOW TO](#how-to)
* [Setup](#setup)
* [Thanx to](#Thanx-to)

## Description`
The [Inav](https://github.com/iNavFlight/inav) since 6.5 version has a feature called "SmartPort Master". This feture enables to connect any FRsky sensor to the FC. It reads data form the sensor and sends it's data to receiver. 
It can be used to add any additonal sensor with SPort protocol. This fearute works only with FPort2/FBus protocol for receiver. 

## HOW TO
SPort is 1 wire serial protocol but [Inav](https://github.com/iNavFlight/inav) uses both RX and TX pin of the Serial to deal with this protocol in "SmartPort Master" feature. 
Inav sends data polling via RX and reads sensorframe which must follow the data polling of the sensor. There are 2 methods of wire this feature : 

1. As described here:  [onewire-over-uart](https://github.com/dword1511/onewire-over-uart)
2. Just shortcut RX and TX line into 1 wire.
3. Use 2 wire Serial as usual.

Which wiring can be used when:    
1. For standard FrSky sensor you can use method 1 nad 2. - Both can be used for inverted UARTS (+3.3v signal level).
   F7 based FC or F4 based with 2 direction inverter (this one is very good - [Inverter](https://quadmeup.com/smartport-inverter-for-f4-flight-controllers/) )
2. For Arduino based sensor with [Pavelsky SPort library](https://www.rcgroups.com/forums/showthread.php?2245978-FrSky-S-Port-telemetry-library-easy-to-use-and-configurable) you can use method 1 nad 2.
   F7 based FC or F4 based with 2 direction inverter (this one is very good - [Inverter](https://quadmeup.com/smartport-inverter-for-f4-flight-controllers/) )
3. For Arduino based sensor and FC with inverted UART (+3.3V signal) or uninverted UART (-3.3V signal) you can use method 3. Example for the code which works as RPM sensor for F4 you can get from this repository.
   It is very early beta verion. Sooner or later I hope i will be able to change it ito fulle usable library for arduino.


## Setup

It has been tested with SpeedyBee f405 Wing and Arduino Nano.
Tho code is set tu use both hardware and software Serial on Arduino. Hadrdware Serial pins are TX0 RX1 (this uart is not inverted). Software Serial pins are D11 - RX. D12 - TX - this is set as uninverted.
It can be inverted by "const bool inversion = true;" (now is false).
Wire it as standard serial FC_RX->Arduino_TX and FC_TX->Arduino_RX, power up arduino form any power source of FC you want. 

In Inav configurator set the UART you have chosen to "SmartPort Master" in Peripherials column - double check it the baudrate is 52600.
Setup receiver to work on FPort2/FBus protocol.
Fire all up and find new sensor in your radio. RPM sensor shall appear. 

## Thanx to 

1. Paweł Spychalski
2. Pavelsky
3. sensei_hacker

   
