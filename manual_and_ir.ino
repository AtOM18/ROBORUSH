//input pins
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
#define S1    5           //sensor (D1)
#define S2    4            //sensor (D2)

#include <ESP8266WiFi.h>
const char WiFiPassword[] = "";//Leave Blank if you do not want to have a password to enter the Node
const char AP_NameChar[] = "DORAEMON";

//speed 
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

//flag for line following
bool flag_line = false;
WiFiServer server(80);

String request = "";


void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  
  Serial.begin(9600);
  WiFi.disconnect();
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();

} 
void goAhead(){ 
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
}

void goBack(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
void goRight(){ 
 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }
 
void goLeft(){
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
void stopRobot(){  
 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
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
  //GET / HTTP/1.1
  if  ( request == "GET /LINE_ON HTTP/1.1" ) {
    flag_line = true;
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "Line mode ON");
    client.flush();
    Serial.println("Line mode ON");
  }
  else if  ( request == "GET /LINE_OFF HTTP/1.1" ) {
    //client.flush();
    flag_line = false;
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "Line mode OFF");
    client.flush();
    Serial.println("Line mode OFF");
  }

  if(!flag_line){
    if  ( request == "GET /F HTTP/1.1" ) {
      Serial.println("F");
        goAhead();
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "F");
    client.flush();
    
  }
   else if  ( request == "GET /B HTTP/1.1" ) {
      Serial.println("B");
        goBack();
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "B");
    client.flush();
    
  }
    if  ( request == "GET /R HTTP/1.1" ) {
      Serial.println("R");
        goRight();
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "R");
    client.flush();
    
  }
    if  ( request == "GET /L HTTP/1.1" ) {
      Serial.println("L");
        goAhead();
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "L");
    client.flush();
    
  }
    else if  ( request == "GET /OFF HTTP/1.1" ) {
      Serial.println("OFF");
        stopRobot();
    //client.flush();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "OFF");
    client.flush();
    
  }
  delay(5);
  }
  else if(flag_line){
    //CODE FOR LINE FOLLOWING
    //S1 Sensor on right side
    Serial.print("Line Follower Mode");
    if(digitalRead(S1)==LOW  && digitalRead(S2)==LOW)
    {
      goAhead();
    }
    if(digitalRead(S1)==HIGH  && digitalRead(S2)==LOW)
    {
      goRight();
    }
    if(digitalRead(S1)==LOW  && digitalRead(S2)==HIGH)
    {
      goLeft();
    }
    if(digitalRead(S1)==HIGH  && digitalRead(S2)==HIGH)
    {
      stopRobot();
    }
  }
  delay(5);
  

} 