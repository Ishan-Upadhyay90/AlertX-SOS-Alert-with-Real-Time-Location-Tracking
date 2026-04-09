#include <SoftwareSerial.h>

SoftwareSerial A9G(10,11); // RX, TX

const int buttonPin = 2;
const int buzzerPin = 8;
const int ledPin = 13;

bool sosTriggered = false;

// ⚠️ Replace with your phone number before using
String phoneNumber = "+91XXXXXXXXXX";

String latitude = "";
String longitude = "";

String line = "";

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  A9G.begin(115200);

  delay(3000);

  Serial.println("SOS System Ready");

  startGPS();
}

void loop() {

  checkIncomingCall();

  int buttonState = digitalRead(buttonPin);

  if(buttonState == LOW && sosTriggered == false) {

    sosTriggered = true;

    Serial.println("SOS Pressed");

    playSOS();

    getGPS();

    sendSMS();

    delay(5000);

    makeCall();
  }

  if(buttonState == HIGH) {
    sosTriggered = false;
  }
}

void checkIncomingCall() {

  if(A9G.available()) {

    String data = A9G.readString();

    Serial.println(data);

    if(data.indexOf("RING") >= 0) {

      Serial.println("Incoming Call - Auto Answer");

      digitalWrite(ledPin, HIGH);

      A9G.println("ATA");
    }

    if(data.indexOf("NO CARRIER") >= 0) {

      Serial.println("Call Ended");

      digitalWrite(ledPin, LOW);
    }
  }
}

void playSOS() {

  // SOS Morse Code

  for(int i=0;i<3;i++){
    tone(buzzerPin,1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }

  for(int i=0;i<3;i++){
    tone(buzzerPin,1000);
    delay(600);
    noTone(buzzerPin);
    delay(200);
  }

  for(int i=0;i<3;i++){
    tone(buzzerPin,1000);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }

}

void startGPS() {

  Serial.println("Starting GPS");

  A9G.println("AT+GPS=1");
  delay(2000);
}

void getGPS() {

  Serial.println("Getting GPS Location...");

  latitude = "";
  longitude = "";
  line = "";

  A9G.println("AT+LOCATION=2");

  unsigned long startTime = millis();

  while(millis() - startTime < 8000)
  {
    while(A9G.available())
    {
      char c = A9G.read();

      if(c == '\n')
      {
        if(line.indexOf(",") > 0)
        {
          int comma = line.indexOf(",");

          latitude = line.substring(0,comma);
          longitude = line.substring(comma+1);

          latitude.trim();
          longitude.trim();

          Serial.print("Latitude: ");
          Serial.println(latitude);

          Serial.print("Longitude: ");
          Serial.println(longitude);

          Serial.print("Google Maps: ");
          Serial.print("https://maps.google.com/?q=");
          Serial.print(latitude);
          Serial.print(",");
          Serial.println(longitude);

          return;
        }

        line="";
      }
      else
      {
        line += c;
      }
    }
  }

  Serial.println("GPS Not Found");
}

void sendSMS() {

  Serial.println("Sending SMS");

  A9G.println("AT+CMGF=1");
  delay(1000);

  A9G.print("AT+CMGS=\"");
  A9G.print(phoneNumber);
  A9G.println("\"");

  delay(1000);

  A9G.print("SOS! Emergency!\nLocation:\n");

  A9G.print("https://maps.google.com/?q=");
  A9G.print(latitude);
  A9G.print(",");
  A9G.print(longitude);

  delay(500);

  A9G.write(26);

  delay(5000);
}

void makeCall() {

  Serial.println("Calling");

  A9G.print("ATD");
  A9G.print(phoneNumber);
  A9G.println(";");

}
