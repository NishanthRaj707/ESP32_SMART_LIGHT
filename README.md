# 🌐 ESP32 Web-Controlled Smart Relay 

![ESP32](https://img.shields.io/badge/ESP-32-blue.svg)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-Code-00979D.svg)
![Relay](https://img.shields.io/badge/Module-5V_Relay-red.svg)

A lightning-fast, non-blocking web server hosted directly on an **ESP32** to control a standard 5V relay module. 

Instead of connecting to your home Wi-Fi, the ESP32 acts as its own Wi-Fi router (Access Point). You just connect your phone to it, open the browser, and tap the buttons to turn your connected devices ON or OFF instantly. Built using the powerful **ESPAsyncWebServer** library for seamless background processing!

---

## 🛠️ Components Used

* **ESP32 Development Board** (Standard or C3 SuperMini)
* **5V Relay Module** (1-Channel)
* **Jumper Wires** (Female-to-Female or Male-to-Female)
* *(Optional)* An external power source if you are switching high-power AC appliances.

---

## ⚡ Circuit Connection

The wiring is incredibly simple. We are using **GPIO 4** for the relay signal.

| Relay Module Pin | ESP32 Pin | Description |
| :---: | :---: | :--- |
| **VCC** / **DC+** | `VIN` | 5V Power Supply to the relay coil |
| **GND** / **DC-** | `GND` | Common Ground |
| **IN** / **Signal**| `GPIO 4` | Control signal from the ESP32 |

> ⚠️ **SAFETY WARNING:** If you are connecting real AC appliances (like a 220V bulb or fan) to the output side of the relay, please be extremely careful. Do not touch the bottom of the relay board while it is plugged into wall power!

---

## ⚙️ Prerequisites

Before uploading the code, ensure you have the required library installed in your Arduino IDE:
* **ESPAsyncWebServer** (Download the `.zip` from GitHub and add via `Sketch > Include Library > Add .ZIP Library`)
* *Note: AsyncTCP is usually handled automatically in the background by the IDE when using this library on modern ESP32 board setups.*

---

## 🧠 Flow of Working (How it Works)

1.  **The Access Point:** When powered on, the ESP32 broadcasts its own Wi-Fi network called `"ESP32_Smart_Light"`.
2.  **The Web Server:** It simultaneously starts an asynchronous web server on port 80 (the standard port for websites). 
3.  **The Interface:** When a user connects to the Wi-Fi and visits `192.168.4.1`, the ESP32 sends back a clean HTML/CSS web page with large "Turn ON" and "Turn OFF" buttons.
4.  **The Action:** * Tapping **"Turn ON"** sends a request to the `/on` route. The ESP32 triggers GPIO 4 `HIGH`, activating the relay, and updates the web page text to "ON".
    * Tapping **"Turn OFF"** sends a request to the `/off` route. The ESP32 drops GPIO 4 `LOW`, deactivating the relay, and updates the text to "OFF".
5.  **Non-Blocking:** Because it is "Async", the ESP32's main `loop()` remains completely empty and free to do other tasks!

---

## 🚀 How to Use

1.  **Clone the Repo:**
   
2.  **Upload the Code:** Open the `.ino` file in the Arduino IDE and upload it to your ESP32.
3.  **Connect to Wi-Fi:** Open your phone or laptop's Wi-Fi settings and connect to:
    * **Network Name:** `ESP32_Smart_Light`
    * **Password:** `12345678`
4.  **Open the Dashboard:** Open Google Chrome or Safari and type `192.168.4.1` into the URL bar.
5.  **Control:** Tap the buttons and hear the relay *click*!

---

### 👨‍💻 Built by BAVA
Happy building! If you found this useful, feel free to star the repository.
