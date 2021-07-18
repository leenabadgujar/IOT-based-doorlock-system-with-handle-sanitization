#include <Servo.h> 
#include <SPI.h> 
#include <MFRC522.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 


#define SS_PIN 4 
#define RST_PIN 5 
MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance.
#define BUZZER 15 //buzzer pin
Servo myServo;
int LED_G = D0;
int LED_R = D8;
char auth[] = "edrmE16-AbvsoT_p4hgukDS0dYUt3Fuk";

char ssid[] = "Haresh";
char pass[] = "87132809";
SimpleTimer timer;
int fflag = 0;
int eflag = 0;
WidgetTerminal terminal(V2); 

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  rfid.PCD_Init();
  Blynk.begin(auth, ssid, pass);
  myServo.attach(2);
  myServo.write(0);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Place your card on the reader...");
  Serial.println();
  timer.setInterval(1000L, iot_rfid);
}

void loop()
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();       
}
 
void iot_rfid()
{
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) 
  {
    return;
  }
//Show UID on serial monitor
  Serial.print("UID tag :");
  Blynk.virtualWrite(V2, "UID tag :" );
  String content= "";
  byte letter;
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(rfid.uid.uidByte[i], DEC);
     Blynk.virtualWrite(V2,rfid.uid.uidByte[i]);
     content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(rfid.uid.uidByte[i], DEC));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  // defining cards here
  if(( content.substring(1) == "25 171 59 178")&& (fflag == 1)) 
  {
    Serial.println("Leena");
    Blynk.virtualWrite(V2, " Leena                       " );
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(500);
    noTone(BUZZER);
    myServo.write(200);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }

  else
  if(( content.substring(1) == "233 170 230 213")&& (eflag == 1)) 
  {
    Serial.println("Anjali");
    Blynk.virtualWrite(V2, " Anjali                      " );
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(500);
    noTone(BUZZER);
    myServo.write(200);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }

 else   {
    Serial.println("unregistered user");
    Blynk.virtualWrite(V2, " Unregistered user Trying to Access your Door Lock                       " );
    Serial.println("---ACCESS DENIED---");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1000);
    delay(1500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}
// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V3)
{
   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable
  // Blynk.virtualWrite(V2, fflag );
 
}
 
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4)
{
   eflag = param.asInt(); // assigning incoming value from pin V4 to a variable
 
}
