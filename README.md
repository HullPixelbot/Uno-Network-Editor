# Uno-Network-Editor
Hosts a web site which can be used to edit programs in a connected Uno powered robot.
![Circuit linking Arduino Uno to Wemos D1 mini via a level converter](images/ESP8266%20to%20Arduino%20Level%20Shifter.png)
The serial ports on the two processors are connected. Note that the usual RX and TX connections on the Wemos D1 mini are not used. Instead the auxillary ports (D8 and D7) are used. This means that it is possible to connect the WEMOS to a computer using the usb connection and program it without having to disconnect the serial connection - which would otherwise interfere with the USB connection to the computer. 

You will need to edit the RobotWebServer.cpp file to set the network credentials of your robot connection. You can also change the local network address of the robot. By default you will find the robot at the following address on your network:

```
http:\\wemos.local
```

When the program starts the pixel on the robot will flash blue and yellow until the robot has connected to the Wi-Fi. It will then turn green to indicate that the robot is connected.
