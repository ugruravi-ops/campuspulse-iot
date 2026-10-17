# CampusPulse — Project Report

**Author:** Ravi · **Domain:** IoT / Environmental Sensing

## 1. Abstract

CampusPulse is a low-cost IoT environmental monitoring node built on the ESP32 microcontroller. The device continuously measures air quality (MQ-135), ambient temperature and humidity (DHT11), and noise levels (KY-037) at a campus location, and streams the data over Wi-Fi to a cloud dashboard (ThingSpeak) every 20 seconds. Local LED indicators provide immediate feedback, and threshold-based alerts flag poor air quality conditions. The total hardware cost is under ₹1,200, making it replicable for multi-node campus deployment.

## 2. Motivation

Campus air quality and thermal comfort directly affect student health and productivity, yet most institutions lack granular, real-time environmental data. A network of cheap, battery-powered sensing nodes can identify pollution hotspots (canteens, labs, high-traffic roads) and provide evidence for infrastructural decisions.

## 3. Objectives

1. Design and build a working IoT sensor node using off-the-shelf components.
2. Stream live multi-parameter environmental data to a cloud platform.
3. Implement local alerting via thresholds.
4. Document the system so it is reproducible by others.

## 4. System Architecture

```
[Sensors]                [ESP32 Node]            [Cloud]           [User]
DHT11 ────────┐
MQ-135 ───────┼── analog/digital ──► ESP32 ── Wi-Fi/HTTP ──► ThingSpeak ──► Live charts
KY-037 ───────┘                    (LEDs: status & alerts)        (CSV export)
```

**Data pipeline:** sensor read (analog/digital) → on-node validation → HTTP GET to ThingSpeak REST API → cloud time-series storage → visualization & CSV export.

## 5. Methodology

- **Temperature/Humidity:** DHT11 single-wire digital protocol, read via Adafruit DHT library.
- **Air quality:** MQ-135 analog output digitized by the ESP32 12-bit ADC (0–4095). The sensor responds to CO₂, NH₃, benzene and smoke; raw ADC values are used as a relative index with an empirically chosen threshold after 30-min warm-up.
- **Noise:** KY-037 analog output; peak amplitude sampled over a 1-second window approximates ambient noise level.
- **Cloud:** ThingSpeak REST `update` endpoint (one write per 20 s, within free-tier limits).
- **Alerting:** node-side thresholds on air quality, temperature, and humidity trigger a red LED blink pattern; green LED confirms a healthy upload cycle.

## 6. Results (Sample)

| Time | Temp (°C) | Humidity (%) | AQ (ADC) | Noise (ADC) | Status |
|------|-----------|--------------|----------|-------------|--------|
| 10:00 | 28.4 | 62 | 870 | 1150 | OK |
| 10:20 | 29.1 | 60 | 1420 | 1980 | ALERT (AQ) |
| 10:40 | 28.8 | 63 | 940 | 1210 | OK |

*(Replace with your actual logged data from the ThingSpeak CSV export.)*

## 7. Limitations & Future Scope

- DHT11 is low-accuracy (±2 °C, ±5%); upgrade to DHT22/BME280 for research-grade data.
- MQ-135 gives *relative*, not calibrated ppm values; calibration against a reference instrument is future work.
- **Planned extensions:**
  - Multiple nodes with MQTT + a central Raspberry Pi gateway.
  - Solar power + deep-sleep duty cycling for multi-day autonomous operation.
  - ML-based anomaly detection on collected time-series (CO₂ drift prediction).
  - Public web dashboard with a map of node locations.

## 8. Skills Demonstrated

Embedded C/C++ programming · ADC interfacing · digital sensor protocols · Wi-Fi networking & REST APIs · cloud IoT platforms · threshold-based control · technical documentation.

## 9. Cost Breakdown

See [circuit.md](circuit.md) — full build ≈ ₹1,100–1,300.

## 10. Reproduction

Full instructions in [setup.md](setup.md); firmware in [code/campuspulse_node.ino](../code/campuspulse_node.ino).
