# 🔌 Circuit & Wiring Guide

All connections use the ESP32 DevKit v1. Use a breadboard and jumper wires (male–female).

## Components

| # | Component | Qty | Approx. Cost (INR) |
|---|-----------|-----|--------------------|
| 1 | ESP32 DevKit v1 (with Wi-Fi + Bluetooth) | 1 | ₹450–600 |
| 2 | DHT11 temperature & humidity sensor (module with pull-up) | 1 | ₹100–150 |
| 3 | MQ-135 air quality sensor (module) | 1 | ₹150–250 |
| 4 | KY-037 sound/noise sensor (analog out) | 1 | ₹50–100 |
| 5 | LEDs — green & red | 2 | ₹10 |
| 6 | Resistors — 220 Ω (LED) | 2 | ₹5 |
| 7 | Breadboard + jumper wires | 1 set | ₹150 |
| 8 | Micro-USB cable (data capable) | 1 | ₹100 |

## Wiring Table

| Sensor Pin | ESP32 Pin |
|------------|-----------|
| DHT11 VCC | 3.3V |
| DHT11 GND | GND |
| DHT11 DATA | GPIO 4 |
| MQ-135 VCC | 5V (VIN) |
| MQ-135 GND | GND |
| MQ-135 AOUT | GPIO 34 (ADC1_CH6) |
| KY-037 VCC | 3.3V |
| KY-037 GND | GND |
| KY-037 AOUT | GPIO 35 (ADC1_CH7) |
| Green LED (+ via 220 Ω) | GPIO 25 |
| Red LED (+ via 220 Ω) | GPIO 26 |
| LED (–) both | GND |

## ⚠️ Important Notes

1. **GPIO 34 & 35 are input-only** — perfect for the analog sensors; don't use them for outputs.
2. **MQ-135 warm-up:** needs 15–30 min for stable readings (24 h burn-in recommended first time). Don't judge readings in the first minutes.
3. **ADC attenuation:** ESP32 ADC reads 0–3.3 V → 0–4095 by default. The MQ-135 works fine at 3.3 V; if you power it at 5 V, ensure its analog output stays under 3.3 V or use a voltage divider.
4. **Power:** the whole setup runs from the ESP32's USB port. For field deployment use a 5 V power bank.
5. Keep sensor wires short (<20 cm) to reduce noise on analog readings.

## Breadboard Layout (ASCII)

```
                    ┌──────────────┐
   DHT11 DATA ──────┤ GPIO4        │
   MQ-135  AOUT ────┤ GPIO34  ESP32│
   KY-037  AOUT ────┤ GPIO35       │
   LED GREEN  ──────┤ GPIO25       │
   LED RED    ──────┤ GPIO26       │
                    │ 3V3 / VIN / GND for sensor power
                    └──────────────┘
```

## Testing Without Wi-Fi

Upload the firmware, open **Serial Monitor at 115200 baud**. Even if Wi-Fi credentials are wrong, sensor values print every 20 s — verify each sensor responds (breathe on DHT11, hold a marker near MQ-135, clap near KY-037).
