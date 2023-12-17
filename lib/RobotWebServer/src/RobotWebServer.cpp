#include <Arduino.h>
#include <ESP8266Webserver.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include "WebPage.h"

const char *ssid = "your SSID here";
const char *password = "your password here";

void sendByteToRobot(byte b)
{
  Serial.print((char)b);
}

void sendStringToRobot(String str)
{
  for (int i = 0; i < str.length(); i++)
  {
    sendByteToRobot(str[i]);
  }
}

void sendNewLineToRobot()
{
  sendByteToRobot('\n');
  sendByteToRobot('\r');
}

void sendLineToRobot(String str)
{
  sendNewLineToRobot();
  sendStringToRobot(str);
  sendNewLineToRobot();
}

ESP8266WebServer server(80);

void handleRoot()
{
  server.send(200, "text/html", webPage);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setupServer()
{

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting WiFi");

  Serial.println("Enabling robot connection");

  delay(200);
  Serial.end();
  Serial.begin(1200);
  Serial.swap();
  delay(200);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    sendLineToRobot("blue");
    delay(250);
    sendLineToRobot("yellow");
    delay(250);
  }

  sendLineToRobot("cyan");

  // Change this string to give the device a different local name on the network.
  
  if (MDNS.begin("wemos"))
  {
    sendLineToRobot("green");
  }

  server.on("/", handleRoot);

  server.on("/run", []()
            {
  Serial.println("Got a run request");
  sendLineToRobot("*RS");
  handleRoot(); });

  server.on("/stop", []()
            {
//    Serial.println("Got a stop request");
    sendLineToRobot("*RH");
    handleRoot(); });

  server.on("/save", []()
            {
    // code is the only argument
    String robotCode = server.arg(0); 
    sendLineToRobot("begin");
    sendStringToRobot(robotCode);
    sendLineToRobot("end");
    handleRoot(); });

  server.onNotFound(handleNotFound);

  server.begin();
}

void updateServer()
{
  server.handleClient();
  MDNS.update();
}
