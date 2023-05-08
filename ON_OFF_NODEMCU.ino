#include <ESP8266WiFi.h>
const char WiFiPassword[] = "";//Leave Blank if you do not want to have a password to enter the Node
const char AP_NameChar[] = "DORAEMON" ;

WiFiServer server(80);

String request = "";
int LED_Pin = 16;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_Pin, OUTPUT);
  digitalWrite(LED_Pin, LOW);//Turn on LED
  delay(400);
  digitalWrite(LED_Pin, HIGH);//Turn off LED
  WiFi.disconnect();
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();

} 

void loop()
{

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');

  if       ( request.indexOf("ON") > 0 )  {
    digitalWrite(LED_Pin, LOW);
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "ON");
    client.flush();
    Serial.println("ON");
  }
  else if  ( request.indexOf("OFF") > 0 ) {
    digitalWrite(LED_Pin, HIGH);
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "OFF");
    client.flush();
    Serial.println("OFF");
  }
  delay(5);

} 