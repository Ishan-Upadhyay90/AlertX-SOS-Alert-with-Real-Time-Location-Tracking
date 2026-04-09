# 🚨 AlertX – SOS Alert with Real-Time Location Tracking

**AlertX** is an Arduino-based emergency alert system that sends an **SOS signal with real-time GPS location** via SMS and phone call. It is designed for personal safety, allowing users to quickly notify emergency contacts at the press of a button.

---

## 📌 Features

- 🆘 One-button SOS trigger  
- 📍 Real-time GPS location tracking  
- 📩 Automatic SMS with Google Maps link  
- 📞 Auto phone call to emergency contact  
- 🔊 SOS buzzer alert (Morse code)  
- 📲 Incoming call auto-answer  
- 💡 LED indicator for call status  

---

## 🛠️ Components Used

- Arduino Board  
- A9G GSM + GPS Module  
- Push Button  
- Buzzer  
- LED  
- Jumper Wires  

---

## 🔌 Circuit Connections

### 🔘 Push Button
- One side → GND  
- Other side → Pin **2**  

### 🔊 Buzzer
- Positive (+) → Pin **8**  
- Negative (–) → GND  

### 💡 LED
- Positive (+) → Pin **13**  
- Negative (–) → GND (via resistor recommended)  

### 📡 A9G Module
- TX → Pin **10** (Arduino RX via SoftwareSerial)  
- RX → Pin **11** (Arduino TX via SoftwareSerial)  
- VCC → 5V  
- GND → GND  

---

## ⚙️ How It Works

1. System initializes GSM and GPS modules  
2. User presses the **SOS button**  
3. System performs:
   - 🔊 Plays SOS buzzer pattern  
   - 📍 Fetches GPS location  
   - 📩 Sends SMS with Google Maps link  
   - 📞 Makes a call to emergency contact  
4. Incoming calls are automatically answered  

---

## 📟 Sample SMS

```

SOS! Emergency!
Location:
[https://maps.google.com/?q=LATITUDE,LONGITUDE](https://maps.google.com/?q=LATITUDE,LONGITUDE)

````

---

## 🚀 Getting Started

1. Replace the phone number in code:
   ```cpp
   String phoneNumber = "+91XXXXXXXXXX";
   ```

2. Connect all components properly
3. Upload the code using Arduino IDE
4. Power the system and wait for initialization
5. Press the button to trigger SOS


## 🏷️ Topics

`arduino` `iot` `gsm` `gps` `a9g-module` `emergency-system`
`sos-alert` `location-tracking` `sms-alert` `call-alert`
`embedded-systems` `personal-safety`


## 💡 Future Improvements

* 📱 Mobile app integration
* 🌐 Cloud tracking dashboard
* 🔋 Battery backup system
* 📍 Continuous live tracking

⭐ If you like this project, give it a star!


