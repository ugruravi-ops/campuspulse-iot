# 🎤 Demo & Interview Guide — CampusPulse

Everything you need to demo the project and answer likely questions when presenting it.

## Part 1: 3-Minute Live Demo Script

**(0:00–0:30) Hook**
> "This is CampusPulse — a ₹1,200 IoT node that measures air quality, temperature, humidity, and noise at a campus spot and pushes it to a live cloud dashboard every 20 seconds."

**(0:30–1:15) Show the hardware**
- Point out each sensor by name: "This is the MQ-135 for air quality, DHT11 for temperature and humidity, KY-037 for noise."
- Show the two LEDs: "Green means a healthy cycle, red means a threshold breach."

**(1:15–2:00) Trigger an alert live**
- Blow/breathe near the MQ-135 or clap near the noise sensor.
- Point at the red LED blink and the Serial Monitor spike. "Local alerting happens on-node — no cloud dependency."

**(2:00–2:45) Show the cloud**
- Open the ThingSpeak channel on your phone/laptop — live charts updating.
- "All four parameters stream over Wi-Fi via a REST API. The data exports as CSV, so you can analyze it in Python or Excel."

**(2:45–3:00) Future scope close**
- "The next steps are multi-node MQTT, solar power with deep sleep, and ML anomaly detection."

## Part 2: Likely Interview Questions & Answers

| Question | Strong Answer |
|-----------|---------------|
| Why ESP32 and not Arduino Uno? | ESP32 has built-in Wi-Fi, dual cores, a 12-bit ADC, and costs only slightly more. The Uno would need an extra Wi-Fi shield — more cost, more wiring, less capability. |
| Why MQTT isn't used (yet)? | For a single node, HTTP REST to ThingSpeak is simpler and within free-tier limits. MQTT becomes the right choice for many nodes — that's on the roadmap, and I understand the tradeoff. |
| Is the MQ-135 output in ppm? | No — the raw ADC value is a *relative* index. True ppm needs calibration against a reference instrument, ideally in a controlled chamber. That's honest engineering scope I've flagged in the report. |
| How accurate is the DHT11? | ±2 °C and ±5% RH. If research-grade data were needed, I'd upgrade to a DHT22 or BME280 — documented in limitations. |
| What happens if Wi-Fi drops? | The node keeps sensing locally and retries Wi-Fi each cycle; it never crashes or hangs — I tested this (test U8 in the test plan). |
| What was the hardest bug? | *(Tell a real story — e.g., analog noise on the long sensor wires, fixed by shortening wires and peak-sampling the noise sensor over a 1-second window.)* |
| Biggest improvement you'd make? | Deep-sleep duty cycling for battery life, and calibration of the MQ-135 — the two things between prototype and research instrument. |
| Why is this useful? | It's a template for any future campus sensor research: swap the sensor, keep the pipeline. The data pipeline (sense → validate → upload → visualize → export) is reusable infrastructure. |

## Part 3: One-Liner Pitch

> "I built a complete, documented, tested IoT sensing node on a ₹1,200 budget — and I have a clear roadmap to turn it from a prototype into a research platform."

## Part 4: Demo Checklist (day before)

- [ ] Firmware flashed and powered by power bank (not laptop — avoids cable chaos)
- [ ] Serial Monitor working as backup if Wi-Fi fails at the venue
- [ ] ThingSpeak channel open in a browser tab on your phone
- [ ] Spare USB cable + fully charged power bank
- [ ] Repo open on laptop: README → report.md → test-plan.md in tabs
