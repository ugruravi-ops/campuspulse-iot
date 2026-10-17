# 📡 CampusPulse — Smart Campus Environment Monitoring Node

An ESP32-based IoT project that continuously monitors **air quality, temperature, humidity, and noise** at a campus location and streams live data to a cloud dashboard. Built as a membership project for **MARVEL R&D Lab**.

> 💡 **What makes this a lab-worthy project:** end-to-end IoT pipeline — sensing → embedded firmware → Wi-Fi networking → cloud REST API → visualization — all under ₹1,200 in parts, fully documented and reproducible.

## 🔍 Features

- 🌡️ **Temperature & Humidity** via DHT11
- 🏭 **Air Quality Index** (relative) via MQ-135 — detects CO₂, NH₃, benzene, smoke
- 🔊 **Ambient Noise** level via KY-037
- ☁️ **Live cloud dashboard** — pushes data to ThingSpeak every 20 s
- 🚨 **Threshold alerts** — on-node LED indicators (green = healthy, red = poor air/thermal comfort)
- ⚡ **Cheap & replicable** — total BOM ≈ ₹1,100–1,300
- 📄 **Lab-style documentation** — wiring, setup guide, and formal project report included

## 🏗️ System Architecture

```
[Sensors]                     [ESP32 Node]                [Cloud]             [User]
DHT11  ── GPIO4 ─┐
MQ-135 ── GPIO34 ┼─ ADC/digital ──► ESP32 ── Wi-Fi/HTTP ──► ThingSpeak ──► Live charts,
KY-037 ── GPIO35 ┘                (green/red LED alerts)    (4 fields)      CSV export
```

## 📊 Live Demo

1. Build the node using [docs/circuit.md](docs/circuit.md) and [docs/setup.md](docs/setup.md).
2. Flash `code/campuspulse_node.ino` with your Wi-Fi + ThingSpeak keys.
3. Watch live charts on your ThingSpeak channel — or open the Serial Monitor (115200 baud) to see readings without Wi-Fi.

**Demo video / live channel link:** *(add yours here after building — paste a YouTube link or ThingSpeak public channel URL)*

## 📁 Repository Structure

| Path | Contents |
|------|----------|
| `code/campuspulse_node.ino` | ESP32 firmware (sensors + Wi-Fi + cloud upload + LED alerts) |
| `docs/circuit.md` | Components list, wiring table, breadboard layout |
| `docs/setup.md` | Full build guide — IDE setup, ThingSpeak config, flashing, troubleshooting |
| `docs/report.md` | Formal project report (abstract, methodology, results, future scope) |

## 🛣️ Roadmap

- [x] Single-node working prototype
- [ ] Solar power + deep-sleep duty cycling for autonomous field operation
- [ ] Multiple nodes → MQTT + Raspberry Pi gateway
- [ ] ML-based air-quality anomaly detection on collected data
- [ ] Public map-based dashboard of node locations

## 🧰 Skills Demonstrated

Embedded C/C++ · ADC & digital sensor interfacing · Wi-Fi networking · REST APIs · cloud IoT platforms · threshold-based control · technical writing

## 🤝 Acknowledgements

Built as a membership application project for **MARVEL R&D Lab**. Special thanks to open-source communities behind Arduino, Espressif (ESP32 Arduino core), and Adafruit sensor libraries.
