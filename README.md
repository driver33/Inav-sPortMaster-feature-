
# Inav sPortMaster feature use 
Documentation and Arduino code for use the [Inav](https://github.com/iNavFlight/inav) sPortMaster feature

## Table of contents
* [Description](#description)
* [HOW TO](#how-to)
* [Setup](#setup)

## Description`
The [Inav](https://github.com/iNavFlight/inav) since 6.5 version has a feature called smartportMaster. This feture enables to connect any FRsky sensor to the FC. It reads data form the sensor and sends it's data to receiver. 
It can be used to add any additonal sensor with SPort protocol. This fearute works only with FPort2/FBus protocol for receiver. 

## HOW TO
SPort is 1 wire serial protocol but [Inav](https://github.com/iNavFlight/inav) uses both RX and TX pin of the Serial to deal with this protocol in smartportMaster feature. 
Inav sends data polling via RX and reads sensorframe which must follow the data polling of the sensor. There are 2 methods of wire this feature : 
1. For standard FrSky sensor it is possible to make it widh diode and resisotr wire as is shown here: [onewire-over-uart](https://github.com/dword1511/onewire-over-uart)
2. For standart FrSky sensor it is possible to make it "brutal": just shortcut RX and TX line into 1 wire.
Both above works with FC with inverted UARTS (+3.3V signal).
3. For Arduino based sensor and FC with inverted UART (+3.3V signal) you can use [Pavelsky SPort library](https://www.rcgroups.com/forums/showthread.php?2245978-FrSky-S-Port-telemetry-library-easy-to-use-and-configurable).
   It Works perfecty and quite easy to use.

However for connecting Arduino based SPort senosr to FC using 1-wire serial with smartportMaster feature looks not very wise:
1. both devices have 2 wires uarts.
2. for FC wth F4 CPU there is an electrical problem with making RX and TX to 1 wire. F4 has not inverted UARTS (-3.3V signal).

Assuming both it is much easier to make 2 wires serial and pass some bytes (2 bytes of data polles sent by FC) through arduino back to the FC.

