#include <ESP8266WiFi.h>

#define TIME_OUT 5000

const char* ssid = "Jarvis";
const char* pass = "ghebhikari";

const char* host = "192.168.0.103";
const char* path = "/getData";
 
void setup() {

Serial.begin(115200);

delay(10);

Serial.println("\n\nConnecting to ");
Serial.print(ssid);

WiFi.begin(ssid,pass);

while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");    
  }

  // After Connection 
  Serial.println("");
  Serial.print("WiFi Connected ");
  Serial.print(ssid);
  Serial.print(" with IP ");
  Serial.println(WiFi.localIP());

  // Wait
  delay(100);
}

void loop() {
  // WiFi client (USE WiFiClientSecure for SSL with PORT = 443)
  WiFiClient client;

  // Port
  const int port = 3000;
  
  // Connect The Client To The Host
  if(!client.connect(host,port))
  {
    Serial.println("Connection failed");
    return;    
  }

  // Sending Request To The Server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: "       + host + "\r\n"          +
               "Connection: close\r\n\r\n"             );

  // Setting Client Timeout
  unsigned long timeout = millis();
  while(client.available() == 0)
  {
    if(millis() - timeout > TIME_OUT)
    {
      Serial.println("Client Timeout");
      client.stop();
      return; 
    }
  }

  // Read The Response 
  while(client.available())
  {
    String line = client.readString(); 
    String json = line.substring(line.lastIndexOf('\r'));
    Serial.println(json);
    //StaticJsonBuffer<200> jsonBuffer;
    //JsonObject& root = jsonBuffer.parseObject(json);

    //String n1 = root["error"];
    //String n2 = root["mature"];
    //String n3 = root["status"];
    //String n4 = root["message"];
    
    
    //Serial.println(n1);
    //Serial.println(n2);
    //Serial.println(n3);
    //Serial.println(n4);
  }
  
  // Delay 10 sec
  delay(10000);
  
}
