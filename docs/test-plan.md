# ✅ Test Plan — CampusPulse Node

Systematic testing performed to validate the node. Each test has an expected result; record actual results after your build.

## 1. Hardware / Unit Tests

| # | Test | Steps | Expected Result | Status |
|---|------|-------|-----------------|--------|
| U1 | Power-on | Connect USB, open Serial Monitor 115200 | Boot message + "Warming up MQ-135..." appears | ☐ |
| U2 | DHT11 read | Breathe on DHT11 for 3–5 s | Humidity % rises visibly on next reading | ☐ |
| U3 | DHT11 accuracy | Compare with a room thermometer | Within ±2 °C (DHT11 spec) | ☐ |
| U4 | MQ-135 response | Hold a marker/alcohol swab 2 cm from sensor | AQ value rises sharply, then decays | ☐ |
| U5 | KY-037 response | Clap 30 cm from sensor | Noise peak value spikes | ☐ |
| U6 | LEDs | During a healthy cycle / triggered alert | Green blinks once; red blinks 3× on alert | ☐ |
| U7 | Wi-Fi connect | Correct SSID/pass | "WiFi connected. IP: x.x.x.x" printed | ☐ |
| U8 | Wi-Fi failure handling | Wrong SSID | Node continues local logging, retries Wi-Fi (no crash/reboot loop) | ☐ |

## 2. Integration Tests

| # | Test | Steps | Expected Result | Status |
|---|------|-------|-----------------|--------|
| I1 | Cloud upload cycle | Let node run 2 min | ≥5 successful uploads; ThingSpeak charts update | ☐ |
| I2 | Rate limiting | Check ThingSpeak responses | No HTTP 400; intervals ≥15 s apart | ☐ |
| I3 | Alert propagation | Trigger AQ threshold (smoke near sensor) | Red LED alert AND cloud field-3 spike visible simultaneously | ☐ |
| I4 | Sensor-failure robustness | Unplug DHT11 mid-run | "DHT11 read failed" logged, no hang/crash, retries next cycle | ☐ |
| I5 | Uptime soak | Run 8+ hours on power bank | No memory crashes/reboots; data continuity in ThingSpeak | ☐ |

## 3. Data Validation Tests

| # | Test | Expected Result | Status |
|---|------|-----------------|--------|
| V1 | Temperature range sane | Readings stay in plausible 5–50 °C band indoors | ☐ |
| V2 | Humidity range sane | Readings stay in plausible 15–95% band | ☐ |
| V3 | AQ baseline stable | After 30-min warm-up, baseline varies <±10% in still air | ☐ |
| V4 | CSV export integrity | ThingSpeak Data Export → CSV has no gaps/garbage | ☐ |

## 4. Sample Results Log (fill after your build)

| Date | Test IDs run | Pass | Fail | Notes |
|------|--------------|------|------|-------|
| YYYY-MM-DD | U1–U8, I1–I5 | 13 | 0 | e.g., "I5 needed power bank >10,000 mAh" |

> 💡 A filled-in test plan with real pass/fail notes is the kind of evidence that separates a tested engineering project from a hobby build.
