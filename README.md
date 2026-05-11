# Digital Clock using Custom LED 7 Segment Display

A handmade 4-digit digital clock built using Arduino Nano, 92 discrete red LEDs, and multiplexing techniques on a Prototype PCB (Dot PCB).

The clock displays time in HH:MM format and includes manual time setting using push buttons.

---

## Features

- 4-digit HH:MM clock display
- Handmade LED 7-segment display
- Multiplexed display control
- Blinking colon indicator
- Manual time setting
- Push button interface
- Common anode display configuration
- Built using Prototype PCB (Dot PCB)

---

## Components Used

- Arduino Nano
- 92 Red LEDs
- Prototype PCB (Dot PCB)
- Push Buttons
- Jumper Wires
- USB Power Supply

---

## LED Distribution

| Component | LED Count |
|---|---|
| 4 Digit Display | 88 LEDs |
| Colon Indicators | 4 LEDs |
| Total LEDs Used | 92 LEDs |

---

## Pin Configuration

### Digit Pins

| Digit | Arduino Pin |
|---|---|
| D1 | D2 |
| D2 | D3 |
| D3 | D4 |
| D4 | D5 |

---

### Segment Pins

| Segment | Arduino Pin |
|---|---|
| A | D6 |
| B | D7 |
| C | D8 |
| D | D9 |
| E | D10 |
| F | D11 |
| G | D12 |

---

### Colon Indicator

| Component | Arduino Pin |
|---|---|
| Colon LEDs | D13 |

---

### Push Buttons

| Button | Arduino Pin |
|---|---|
| MODE | A3 |
| UP | A4 |
| DOWN | A5 |

---

## Working Principle

The clock uses multiplexing to control all four digits efficiently using shared segment lines. The Arduino Nano rapidly refreshes each digit individually, creating the illusion of a continuously illuminated display.

Timekeeping is handled using the Arduino millis() timer function, while push buttons allow manual adjustment of hours and minutes.

The blinking colon LEDs act as a visual seconds indicator.

---

## Files Included

- Arduino Source Code
- Project Documentation
- Circuit Images
- Project Photos

---

## Future Improvements

- RTC Module for Accurate Timekeeping
- Alarm Functionality
- Brightness Control
- Battery Backup
- WiFi Time Synchronization
- Custom PCB Design

---

## Preview

<img width="420" height="306" alt="image" src="https://github.com/user-attachments/assets/e0e79f80-8494-443a-919d-c671ea145e1e" />
<img width="493" height="307" alt="image" src="https://github.com/user-attachments/assets/8d7033fc-655b-4548-a66d-ec3376afb304" />
<img width="526" height="365" alt="image" src="https://github.com/user-attachments/assets/69f18304-3870-4bed-aeb9-a2577232c391" />

---

## License

MIT License
