# 🛠️ Setup Guide — Build CampusPulse in 1 Day

## Part A: Software Setup (~30 min)

### 1. Install Arduino IDE
Download from https://www.arduino.cc/en/software and install.

### 2. Add ESP32 board support
- **File → Preferences → Additional Boards Manager URLs**, paste:
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
- **Tools → Board → Boards Manager** → search `esp32` → **Install** (Espressif Systems).
- **Tools → Board → ESP32 Arduino → ESP32 Dev Module**.

### 3. Install the DHT library
**Sketch → Include Library → Manage Libraries** → search `DHT sensor library` by Adafruit → Install (accept dependencies).

### 4. ThingSpeak channel (free cloud dashboard)
1. Sign up at https://thingspeak.com with a free MathWorks account.
2. **Channels → New Channel**, name it `CampusPulse`, enable **4 fields**:
   - Field 1: Temperature (°C)
   - Field 2: Humidity (%)
   - Field 3: Air Quality (raw ADC)
   - Field 4: Noise (raw ADC)
3. Save, then go to **API Keys** tab → copy the **Write API Key**.

### 5. Configure firmware
Open `code/campuspulse_node.ino` and fill in:
```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* TS_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";
```

## Part B: Hardware Assembly (~1 hour)

Follow the wiring table in [circuit.md](circuit.md). Order:
1. Place ESP32 on breadboard.
2. Wire DHT11 → GPIO 4.
3. Wire MQ-135 AOUT → GPIO 34 (power MQ-135 from 5V/VIN).
4. Wire KY-037 AOUT → GPIO 35.
5. Wire both LEDs with 220 Ω resistors → GPIO 25 (green), GPIO 26 (red).

## Part C: Flash & Test (~15 min)

1. Connect ESP32 via USB → **Tools → Port** → select the COM port.
2. If upload fails with "Connecting....", hold the **BOOT** button on the ESP32 while it says Connecting, then release.
3. Open **Serial Monitor (115200 baud)** — sensor values print every 20 s.
4. Check ThingSpeak → your channel → readings appear as live charts within a minute.

## Part D: Field Deployment (optional but impressive for the lab)

- Power with a 5V power bank; node runs standalone.
- Place near a lab window/roadside to capture real variation.
- ThingSpeak lets you **export CSV** (channel → Data Export) for analysis in Excel/Python.

## Troubleshooting

| Problem | Fix |
|---|---|
| DHT11 reads `nan` | Check DATA wire on GPIO 4; use a DHT11 **module** (has pull-up built-in) |
| MQ-135 always max (4095) | Still in warm-up — wait 30+ min, or adjust the onboard trim pot |
| ThingSpeak returns -1 or 0 | Check API key, Wi-Fi, and that 15+ s passes between updates |
| Upload fails | Hold BOOT button during "Connecting....." |
| ADC noise | Keep wires short; average multiple reads |
