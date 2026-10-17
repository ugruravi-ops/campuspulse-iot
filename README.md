# 📡 CampusPulse — Smart Campus Environment Monitoring Node

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20(Arduino)-teal)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-orange)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Prototype%20Working-brightgreen)

An ESP32-based IoT project that continuously monitors **air quality, temperature, humidity, and noise** at a campus location and streams live data to a cloud dashboard every 20 seconds.

> 💡 **Why this project matters:** a complete end-to-end IoT pipeline — sensing → embedded firmware → Wi-Fi networking → cloud REST API → visualization — built for under ₹1,200 in parts, fully documented and reproducible.

## 🔍 Features

- 🌡️ **Temperature & Humidity** via DHT11
- 🏭 **Air Quality Index** (relative) via MQ-135 — detects CO₂, NH₃, benzene, smoke
- 🔊 **Ambient Noise** level via KY-037
- ☁️ **Live cloud dashboard** — pushes data to ThingSpeak every 20 s
- 🚨 **Threshold alerts** — on-node LED indicators (green = healthy, red = poor air/thermal comfort)
- ⚡ **Cheap & replicable** — total BOM ≈ ₹1,100–1,300
- 📄 **Professional documentation** — wiring, setup guide, formal report, and a systematic **test plan**

## 🏗️ System Architecture

```
[Sensors]                     [ESP32 Node]                [Cloud]             [User]
DHT11  ── GPIO4 ─┐
MQ-135 ── GPIO34 ┼─ ADC/digital ──► ESP32 ── Wi-Fi/HTTP ──► ThingSpeak ──► Live charts,
KY-037 ── GPIO35 ┘                (green/red LED alerts)    (4 fields)      CSV export
```

## 📁 Repository Structure

| Path | Contents |
|------|----------|
| `code/campuspulse_node.ino` | ESP32 firmware (sensors + Wi-Fi + cloud upload + LED alerts) |
| `docs/circuit.md` | Components list with costs, wiring table, breadboard layout |
| `docs/setup.md` | Full build guide — IDE setup, ThingSpeak config, flashing, troubleshooting |
| `docs/report.md` | Formal project report (abstract, methodology, results, future scope) |
| `docs/test-plan.md` | Unit, integration & data-validation tests with pass/fail checklist |
| `docs/demo-guide.md` | 3-minute demo script + likely interview Q&A |
| `screenshots/` | Guide for adding project photos to the README |
| `LICENSE` | MIT — free to reuse and extend |

## 📊 Live Demo

1. Build the node using [docs/circuit.md](docs/circuit.md) and [docs/setup.md](docs/setup.md).
2. Flash `code/campuspulse_node.ino` with your Wi-Fi + ThingSpeak keys.
3. Watch live charts on your ThingSpeak channel — or open the Serial Monitor (115200 baud) to see readings without Wi-Fi.

**Demo video / live channel link:** *(add yours here after building — paste a YouTube link or ThingSpeak public channel URL)*

## 🛣️ Roadmap

- [x] Single-node working prototype
- [x] Full documentation + test plan
- [ ] Solar power + deep-sleep duty cycling for autonomous field operation
- [ ] Multiple nodes → MQTT + Raspberry Pi gateway
- [ ] ML-based air-quality anomaly detection on collected data
- [ ] Public map-based dashboard of node locations

## 🧰 Skills Demonstrated

Embedded C/C++ · ADC & digital sensor interfacing · Wi-Fi networking · REST APIs · cloud IoT platforms · threshold-based control · systematic testing · technical writing

## 📜 License

Released under the [MIT License](LICENSE) — you're free to build, modify, and extend this project. If you build a node, a star on the repo is appreciated! ⭐

## 🤝 Acknowledgements

Special thanks to the open-source communities behind Arduino, Espressif (ESP32 Arduino core), and Adafruit sensor libraries.
