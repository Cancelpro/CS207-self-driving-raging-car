# CS207-self-driving-raging-car

This is a repository for a Self-Driving Arduino car. 

So this vehicle uses a hypersonic sensor to look ahead and find any objects that it might hit along the way. If it finds an object directly ahead of it, it will move backwards for 1 second and then turn right.
If the vehicle collides with an object two times total, it will scream "NOO" and drive back and forth in an upset manner.

![alt text][pic1]

[pic1]: https://github.com/Cancelpro/CS207-self-driving-raging-car/blob/main/img/pic2.jpg "Head on Shot"


Repository Contents
============

Here's a map of what I have to offer:
* **/src** - This includes my uncompiled script to get the vehicle running.
* **/hardware** - The fritzing file so you can view the circuit.
* **/img** - Where all the vehicle images and circuit images belong.
* **/LICENSE** - Runs off of the MIT license so feel free to use whatever you want.
* **/README** - This is purely for github.

Requirements and Materials
============

Dependencies:
* TMRpcm Library: https://github.com/TMRh20/TMRpcm


Required Materials:
* 1 x UltraSonic Sensor
* 1 x DC motor Controller
* 1 x 8 ohm speaker
* 1 x Micro sd card (any size will do)
* 1 x Arduino sd card module
* 1 x 6.7k resistor
* 1 x Small Breadboard
* 1 x Battery compartment
* 1 x BC 556 Transistor
* 1 x car chasis kit

Build Instructions
============
 
 ![alt text][pic3]

[pic3]: https://github.com/Cancelpro/CS207-self-driving-raging-car/blob/main/img/pic3.jpg

Here is is a visual representation of the circuit. (I seriously tried to keep it as clean as possible)

 ![alt text][pic4]

[pic4]: https://github.com/Cancelpro/CS207-self-driving-raging-car/blob/main/img/pic4.jpg

Usage
============
* You need to upload the code to your arduino UNO
* Make sure your arduino is hooked up to an external power source.
* Confirm your SD card has an 8 bit mono wav file of 16000hz titled "no.wav"
* put it on the floor and have fun! (Note: I have no switches, I ran out of ports.)

The Team
============
This took me forever to put together, so many people worked on this project. took me hours to type out and list all the people who worked on this.
* Tait Larsen


Credits
============
* Sarvagnya Purohit: I borrowed their code and circuitry from: https://maker.pro/arduino/projects/arduino-audio-player
* Dejan: I used his guide for my DC motor controller and used some of his code provided here: https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
* Dejan: I used his sample code to get my Ultrasonic Sensor working: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
* Vitor Vargas Santos: For his original Self Driving car idea: https://www.instructables.com/How-to-Build-Arduino-Self-Driving-Car/
