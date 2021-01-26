# Smart-Robot-Car-with-Distributed-and-Interactive-System
## Introduction
This project aims to design a Smart Robot Car with Distributed and Interactive System. The robot car can move around a place automatically avoiding obstacles and also reacts to certain human interactions. It can sense different parameters and returns information through distributed system.The robot is using distributed system through communication between microcontrollers Arduino Uno and ESP32. It is possible to send data from ESP32 to Arduino Uno. There are sensors and receivers connected to both ESP32 and Arduino Uno to control it under different conditions and make the system interactive. Two dc motors are used with L298N motor driver and connected to Uno to move the car in different directions. An ultrasonic sensor is connected to Arduino Uno along with servo motor to avoid obstacles. DHT11 humidity and temperature sensor is also interfaced to ESP32 to measure the humidity and temperature. These values are sent to Arduino Uno through I2C communication. An IR receiver (to ESP32) with IR remote control is also used to control the robot manually which makes the system interactive. There are LEDs and the sound sensor also used to highlight the interactions under certain conditions. 
## Instructions for using codes
### For ESP
To use ESP as master device,
Open ESP_Master.ino with Arduino IDE
Connect ESP using USB
Upload the code to the board
### For Arduino
To use Arduino as slave,
Open the code Robot_Car_control_Arduino.ino with Arduino IDE 
Connect Arduino using USB
Upload the code to the board
