#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>
#include"FS.h"
#include <Servo.h>
Servo servo;

/* Put your SSID & Password */
const char* ssid = "Lil-BoT";  // Enter SSID here
const char* password = "123456789";  //Enter Password here


int counter=100;

//Magnet pin
int magnetPin = D8;

ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial.begin(9600);

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  /*Serial.println("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());*/
  delay(100);
  
  server.on("/",   homepage);
  server.on("/B",  Backward);
  server.on("/F",  Forward);
  server.on("/L",  Left);
  server.on("/R",  Right);
  server.on("/S",  state);
  server.on("/SA", swingArm);
  server.on("/SC", seizeCoin);
  server.on("/M",  Movement);
  server.on("/K",  Knowme);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  /*Serial.println("HTTP server started");*/

  pinMode(magnetPin, OUTPUT);
  digitalWrite(magnetPin, HIGH);

  servo.attach(D7);
  servo.write(75);
}
Z
void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}


void homepage() {
  
  server.send(200, "text/html", Home()); 
  //Serial.println("Home page loaded");
}



void Knowme(){
  server.send(200, "text/html", know());
  //Serial.println("They know me well now ");
}

void Movement(){
  server.send(200, "text/html", control(counter));
  //Serial.println("Control accessed ...");
}
void Backward(){
  //Serial.println("I took a step backward...");
  Serial.println('B');
 
}

void Forward() {
  /*Serial.println("I took a step forward...");*/
  Serial.println('F');
}

void Left(){
  /*Serial.println("I took a step to the Left ...");*/
  Serial.println('L');
  
}

void Right() {
  /*Serial.println("I took a step to the Right ...");*/
  Serial.println('R');
}



void state(){
  //Serial.println("I was switched ON");
  Serial.println('S');
}

void swingArm(){
  //Serial.println("You took control over my arm");
  for(int i = 75; i >= 5; i -= 10){
      servo.write(i);
      delay(300);
  }
  delay(1000);
  for(int i = 5; i <= 75; i += 10){
      servo.write(i);
      delay(300);
  }
  delay(500);
}

void seizeCoin(){
  //Serial.println("I collected a coin");
  digitalWrite(magnetPin, LOW);
  counter++;
}

void handle_NotFound(){
  server.send(200, "text/html", notFound());
  //Serial.println("Couldn't establish connection");
}

//HTML code for Homepage

String Home(){

  String html ="<!DOCTYPE html> \n";
  html+= "<html lang=\"en\" dir=\"ltr\">\n";
  html+= "<head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html+= " <title>| Lil-BoT |</title> \n";
  html+= "<style media=\"screen\"> nav { text-align:center; }\n"; 
  html+= "nav ul li{ display: inline-block; margin-right: 200px; margin-left: 150px; font-size: 12px; } \n";
  html+= " a{ text-decoration:none; } \n"; 
  html+= ".btn{ display: inline-block; font-size: 16px; font-family: monospace; background-color: #000000; background-image: linear-gradient(315deg, #000000 0%, #414141 74%); color: #a1a1a1; padding: 8px 30px; margin: 30px 0; border-radius: 30px; }\n";
  html+= ".btn:hover { background-image: linear-gradient(315deg, #000000 0%, #ffeaa7 74%); background-color: #000000; color: #000000; }\n";
  html+= " </style>\n";
  html+= "</head> \n";
  html+= "<body style=\"background-image: url('Lil-Bot.png')\">\n"; 
  html+= " <div class=\"Navigation\"> <nav> <ul> <li><a href=\"/M\" class=\"btn\">Control</a></li> <li><a href=\"/K\" class=\"btn\">Know Me</a></li> </ul> </nav> </div> \n";
  html+= " </body>\n"; 
  html+= "</html>\n";
  return html;

}

//Control page a la Counter
String control(int counter){
String control ="<!DOCTYPE html>\n";
control+="<html lang=\"en\" dir=\"ltr\"> \n";
control+="<head> <meta charset=\"utf-8\">\n"; 
control+="<title>Control</title>\n"; 
control+="<style media=\"screen\"> body{ background-image:url(\"MBK.png\"); background-color:#000000; }\n"; 
control+=".btn{ background-image: linear-gradient(-30deg, #515A5A 0%, #000000 90%); color:#979A9A; font-size: 16px; font-family: monospace; text-transform: uppercase; border-radius: 20px; width: 200px; height: 100px; }\n";
control+=".btn:hover{ animation-duration: 0.5s; transition-duration: 0.5s; transition-property: 0.5s; -moz-transform: translate(0px, -5px); -ms-transform: translate(0px, -5px); -o-transform: translate(0px, -5px); transform: translate(0px, -5px) } \n";
control+="td{ padding-bottom: 10px; }\n";
control+="table{ align:center; margin-top:200px; margin-left:100px; }\n";
control+="h1{align-content: center;} \n";
control+=".bt{display: inline-block; font-size: 16px; font-family: monospace; background-color: #000000; background-image: linear-gradient(315deg, #000000 0%, #414141 74%); color: #a1a1a1; padding: 8px 30px; margin: 30px 0; border-radius: 30px; margin-right: 200px; margin-left: 115px;}\n";
control+="p {color:#a1a1a1;}\n";
control+="</style>\n"; 
control+="</head>\n"; 
control+="<body> \n";
control+="<h1><button class=\"bt\" >No. of coins counted:";
control+=(int)counter;
control+="</button>\n";
control+="</h1>\n";
control+="<div class=\"container\" > <table> <tr> <td>1</td> <td ><a href=\"/F\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Forward</button></a></td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td><a href=\"/SA\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Swing <br> Arm</button></a></td> </tr> <tr> <td ><a href=\"/L\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Left</button></a></td> <td >></td> <td ><a href=\"/R\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Right</button></a</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td><a href=\"/S\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Switch</button></a></td> </tr> <tr> <td>1</td> <td ><a href=\"/B\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Backward</button></a></td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td>80</td> <td><a href=\"/SC\"><button class=\"btn\" style=\"margin-left:15px;height: 90px; width: 100px;\">Seize Coin</button></a></td> </tr> </table> </div>\n";
control+="</body>\n";
control+="</html>\n";
return control;
}

//HTML code for info. page
 String know(){
 String know ="<!DOCTYPE html>\n";
 know+="<html lang=\"en\" dir=\"ltr\">\n"; 
 know+="<head> <meta charset=\"utf-8\"> \n";
 know+="<title>About Lil-Bot</title> \n";
 know+="<style media=\"screen\"> body{ background-image:url(\"info.jpg\"); background-repeat: no-repeat; } \n";
 know+="</style>\n"; 
 know+="</head> \n";
 know+="<body> \n";
 know+="</body> \n";
 know+="</html>\n";
 return know;
}

// HTML code for 404
 String notFound(){
 String notfound ="<!DOCTYPE html>\n";
 notfound+="<html lang=\"en\" dir=\"ltr\">\n"; 
 notfound+="<head> <meta charset=\"utf-8\"> \n";
 notfound+="<title>ERROR 404</title> \n";
 notfound+="<style media=\"screen\"> body{ background-image:url(\"404.jpg\"); background-repeat: no-repeat; } \n";
 notfound+="</style>\n"; 
 notfound+="</head> \n";
 notfound+="<body> \n";
 notfound+="</body> \n";
 notfound+="</html>\n";
 return notfound;
}

  
