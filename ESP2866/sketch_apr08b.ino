#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define led LED_BUILTIN
#define RX  3 //ESP UART RX PIN 
#define TX  1 //ESP UART TX PIN 

char * ssid = "LINKDSL-a";
char * password= "*Command15486";


WiFiServer server(80);
SoftwareSerial espSerial(RX,TX);

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  delay(10);
  pinMode(led , OUTPUT);
  digitalWrite(led, LOW);//led on

  //Serial.println();
  //Serial.println();
  //Serial.println("connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi Connected");

  server.begin();
  //Serial.println("server Started");
  //Serial.println("Use this URL to Connect: ");
  //Serial.println("http://");
  //Serial.print(WiFi.localIP());
  //Serial.print("/");
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  }
  //Serial.println("New Client");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type: text/html");
  client.println("");

  client.print("<!DOCTYPE HTML>");
  client.print("<html>");
  client.print("<head>");
  client.print("<meta charset=\"utf-8\">");
  client.print("<meta name=\"descriptio\" content=\"ESP Test\">");
  client.print("</head>");
  client.print("<body>");
  client.print("<h1>ESP Control Practice</h1>");
  client.print("<h3>Khaledfathi@protonmail.com</h3>");
  client.print("<br><hr>");
  client.print("<div style=\"margin:0px auto;width:700px;font-size:50px;text-align:center;\">");
  client.print("<label>LED 0</label>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED0ON\">ON</a>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED0OFF\">OFF</a>");
  client.print("<br>");
  client.print("<label>LED 1</label>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED1ON\">ON</a>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED1OFF\">OFF</a>");
  client.print("<br>");
  client.print("<label>LED 2</label>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED2ON\">ON</a>");
  client.print("<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<span>");
  client.print("<a href=\"/LED2OFF\">OFF</a>");
  client.print("</div>");
  client.print("<br><hr>");
  client.print("</body>");
  client.print("</html>");

  while (!client.available()){
     delay(1);
  }
  String request= client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  //send starting customframe
  espSerial.print("com");//command indicator
  if(request.indexOf("/LED0ON")!=-1){
    espSerial.print('A');
  }else if(request.indexOf("/LED0OFF")!=-1){
    espSerial.print('a');
  }else if(request.indexOf("/LED1ON")!=-1){
    espSerial.print('B');
  }else if(request.indexOf("/LED1OFF")!=-1){
    espSerial.print('b');
  }else if(request.indexOf("/LED2ON")!=-1){
    espSerial.print('C');
  }else if(request.indexOf("/LED2OFF")!=-1){
    espSerial.print('c');
  }
  
}
