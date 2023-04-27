
#include <WiFi.h>

const char *ssid_Router     =  "SalmonMeatball";  //Enter the router name  "Berkeley-IoT"
const char *password_Router =  "20220804";        //Enter the router password  "5D&sl3k#"
#define     REMOTE_IP          "10.0.0.38"        //input the remote server which is you want to connect 
#define     REMOTE_PORT         8888              //input the remote port which is the remote provide
WiFiClient client;

//for potentiometer
const int poten = 34;
int poten_value;
String poten_value_String;
const int poten2 = 35;
int poten_value2;
String poten_value2_String;


void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid_Router, password_Router);
  Serial.print("\nWaiting for WiFi... ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);

  Serial.print("Connecting to ");
  Serial.println(REMOTE_IP);

  while (!client.connect(REMOTE_IP, REMOTE_PORT)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting a moment before retrying...");
  }
  Serial.println("Connected");

}

void loop() {

  /*
    poten_value = analogRead(poten);
    poten_value_String = String(poten_value);
    client.print(poten_value_String.length());    //transmit the length of the data
    client.print(poten_value);                    //transmit the data itself

    Serial.print(poten_value_String.length());
    Serial.print('\t');
    Serial.println(poten_value);
  */

  if (client.connected() > 0) {

    //transmit first data
    poten_value = analogRead(poten);
    poten_value_String = String(poten_value);
    client.print(poten_value_String.length());    //transmit the length of the data
    client.print(poten_value);                    //transmit the data itself


    //transmit second data
    poten_value2 = analogRead(poten2);
    poten_value2_String = String(poten_value2);
    client.print(poten_value2_String.length());    //transmit the length of the data
    client.print(poten_value2);                    //transmit the data itself

    Serial.print(poten_value_String.length());
    Serial.print('\t');
    Serial.print(poten_value);
    Serial.print('\t');
    Serial.print(poten_value2_String.length());
    Serial.print('\t');
    Serial.println(poten_value2);
  }

  if (client.connected () == 0) {
    client.stop();
    WiFi.disconnect();
  }

  delay(100);
}
