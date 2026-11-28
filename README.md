# Embedded Learning Journey

I'm a 3rd-year Electrical Engineering student at Western Sydney University, learning embedded systems from the ground up: Arduino UNO first, then ESP32, then STM32. I'm also learning circuit design along the way, from paper schematics to KiCad and my own PCBs.

This repo is my daily log. Each `dayNN` folder holds that day's sketches, one folder per sketch (open the `.ino` file in the Arduino IDE). Serial Monitor runs at **115200 baud**.

## Plan (about 15 weeks)

| Weeks | Firmware | Hardware |
|---|---|---|
| 1–4 | C basics, LEDs, buttons, sensors (Arduino UNO, then ESP32) | Schematic symbols, resistors, voltage dividers, pull-ups, transistors, start KiCad |
| 5–6 | DIY IoT: displays, Wi-Fi, phone-controlled devices | Power supplies, regulators, reading datasheets |
| 7–10 | STM32 the professional way: HAL, timers, interrupts, I2C, SPI, FreeRTOS | Analog circuits, then my first PCB (weeks 9–10) |
| 11–15 | A finished project to show employers | A custom PCB for that project, made at JLCPCB |

## Progress

| Day | Topic | Sketches |
|---|---|---|
| 1 | Blink, digital output | [blink](day01/blink), [led-chaser](day01/led-chaser) |
| 2 | Variables, for loops, Serial | [variables-kitt](day02/variables-kitt), [speed-up-celebrate](day02/speed-up-celebrate), [blink-counter-serial](day02/blink-counter-serial) |
| 3 | Operators, Ohm's law, int vs float division | [operators-ohms-law](day03/operators-ohms-law) |
| 4 | if/else, logic operators, analog input, buttons | [if-else-voltage-warning](day04/if-else-voltage-warning), [led-current-check](day04/led-current-check), [button-led](day04/button-led), [logic-leap-year](day04/logic-leap-year) |
| 5 | for and while loops, break, polling a button | [count-up](day05/count-up), [countdown](day05/countdown), [even-numbers](day05/even-numbers), [sum-1-to-100](day05/sum-1-to-100), [resistor-sweep](day05/resistor-sweep), [while-doubling](day05/while-doubling), [battery-hours](day05/battery-hours), [break-infinite-loop](day05/break-infinite-loop), [wait-for-button](day05/wait-for-button) |
| 6 | Reading user input over Serial; Ohm's law calculator; choosing LED resistors | [serial-blink-count](day06/serial-blink-count), [ohms-law-calculator](day06/ohms-law-calculator), [rgb-led-sequence](day06/rgb-led-sequence) |
| 7 | Review week 1; button edge detection and debounce | [rgb-color-cycler](day07/rgb-color-cycler) |
| 8 | Functions: parameters, return values, guard clauses, input validation; electrical calculators (power, LED resistor, % error) | [functions](day08/functions) |
| 8 | Arrays: LED pins in an array, LED modes with a button | [arrays](day08/arrays) |
| 9 | Button edge detection + debounce on ESP32 (one LED at a time with a button) | [button](day09/button) |
| 9 | Arrays: average, highest and lowest of 7 temperatures (handles ties and all-negative input) | [temperature](day09/temperature) |
| 10 | ESP32: setup() vs loop(), global vs local variables, double blink, doing something exactly N times with a bool flag | [loop-counter](day10/loop-counter), [double-blink](day10/double-blink), [blink-5-times-setup](day10/blink-5-times-setup), [blink-5-times-loop](day10/blink-5-times-loop) |
| 11 | millis(): timing without delay(), LEDs blinking at different rates with arrays, a button that never misses a press (delay vs millis, debounce with millis) | [print-time](day11/print-time), [blink-one-led](day11/blink-one-led), [blink-led-array](day11/blink-led-array), [button-delay](day11/button-delay), [button-millis](day11/button-millis) |
| 12 | ESP32 ADC with analogRead(): potentiometer to percent, LED bar graph, averaging 10 readings, printing only on a 2% change, knob controls blink speed | [led-bar](day12/led-bar), [smooth-blink](day12/smooth-blink) |
| 13 | PWM with analogWrite(): 5 brightness levels, a breathing LED with millis, a knob that dims an LED (constrain), and a 3-LED bar that fades in section by section, gamma correction (squaring) so brightness looks even to the eye | [brightness-levels](day13/brightness-levels), [breathing-led](day13/breathing-led), [pot-brightness](day13/pot-brightness), [fading-led-bar](day13/fading-led-bar), [gamma-brightness](day13/gamma-brightness) |
| 14 | Bits and hex: printing numbers in BIN/HEX, a 4-LED binary counter (bitRead and count & (1 << i)), a 4-LED fading bar using >> 2 instead of percent, one byte holding 4 LED states toggled with XOR and a debounced button (millis), and a bit-shift LED chaser | [number-formats](day14/number-formats), [binary-counter](day14/binary-counter), [shift-brightness-bar](day14/shift-brightness-bar), [led-mask](day14/led-mask), [bit-chaser](day14/bit-chaser) |
| 15 | Project: traffic light state machine with millis (no delay), debounced pedestrian button that ends green early, potentiometer sets green time 3–10 s, 7-segment countdown using one byte per digit (lookup table + bitRead), first KiCad schematic | [traffic-light](projects/traffic-light) |
| 17–18 | Pointers: printing variable addresses (& and *), addresses inside an array 4 bytes apart and the garbage one slot past the end, swapping two variables through pointers vs. by copy, and a readKnob() function that "returns" two values (raw ADC and brightness) through pointers | [pointer-basics](day17/pointer-basics), [array-addresses](day17/array-addresses), [swap-values](day17/swap-values), [read-knob](day17/read-knob) |
| 19 | Pointers and arrays: an array name is the address of its first element, `p + 1` moves one element (4 bytes for `int`, 1 for `byte`), `sizeof` gives 12 for the array but 4 inside a function (just the address); filling an array of 8 ADC samples and averaging it through functions that take a pointer + count; pointer drills: clamp a variable in place, split milliseconds into minutes and seconds, add a number to every element | [array-steps](day19/array-steps), [pot-average](day19/pot-average), [clamp-value](day19/clamp-value), [split-time](day19/split-time), [add-to-all](day19/add-to-all) |
| 19 | Structs: one `Led` struct (pin, last toggle time, on/off, interval) for 3 LEDs blinking at different speeds with millis, then an `updateLed(Led*)` function using `->`. Hardware: RC low-pass filter turning PWM into a steady voltage, ripple measured with the ADC for no cap / 100 nF / 1 µF / 10 µF (3029 → 60 mV), schematic in KiCad | [struct-blink](day19/struct-blink), [struct-blink-function](day19/struct-blink-function), [rc-ripple](day19/rc-ripple), [rc-filter schematic](day19/rc-filter-kicad/rc-filter.pdf) |
| 20 | Project: night light with 3 modes (off / on / auto) on one button. In ON the pot sets brightness with gamma correction (`(x/255)^2.2 * 255`) so the knob feels even to the eye; the last brightness is remembered. In AUTO the pot stands in for a light sensor with hysteresis (on below 1200, off above 1500) so it never flickers. All settings live in one `NightLight` struct, and the auto logic takes a `NightLight*`. Schematic in KiCad (LED + 220 Ω on GPIO18, button to GND with internal pull-up on GPIO4, 10k pot on GPIO34) | [night-light](day20/night-light), [night-light schematic](day20/night-light-kicad/nightlight.pdf) |
| 22 | Splitting a sketch into files: `.h` = the menu (struct, constants, function prototypes, `#pragma once`), `.cpp` = the kitchen (function bodies, `#include <Arduino.h>`). The night light split into `NightLight.h/.cpp` with functions taking a `NightLight*`, plus a reusable debounced `Button` module (`Button.h/.cpp`) dropped unchanged into a press counter. Compile vs linker errors, why `#define` is risky (`SQUARE(1 + 2)` = 5). Hardware: diode-mode Vf of red/yellow/green LEDs (1.76 / 1.82 / 1.84 V), why a drone uses a Schottky for reverse-battery protection (0.3 W vs 0.7 W lost at 1 A), Zener as a voltage clamp | [night-light-split](day22/night-light-split), [button-counter](day22/button-counter) |
| 23 | `switch` and `enum`: states get names instead of magic numbers (`enum Mode`, `enum LightState`), `switch` with `break`/`default`, intentional fall-through to share code between cases, and why an `int` must be cast back to the enum type. The night light's mode logic rewritten with two switches; the traffic light rebuilt as a proper state machine (each state names its next state) and extended with a 1 s red+yellow "get ready" state by adding one enum name, one interval and one case. Hardware: NPN transistor as a low-side switch, base resistor sizing (60 mA load, hFE 100, 5x overdrive -> 3 mA -> 820 Ω) | [night-light-enum](day23/night-light-enum), [traffic-light-enum](day23/traffic-light-enum) |
| 24 | Sound with a passive buzzer: frequency vs period, a hand-made square wave (`digitalWrite` + `delayMicroseconds`, half period = 1,000,000 / (2 × f) µs) played for a set time with `millis()`, then `tone()`/`noTone()` which run on a hardware timer and don't block. A melody player state machine (`enum PlayerState`, `switch` every loop, button checked inside each case) using the ESP32 BOOT button (GPIO0): press to play Twinkle Twinkle in a loop, press again to stop. The night light now reads a real LDR in a voltage divider (room light 4095, covered 800; on below 1200, off above 1500). Hardware: passive buzzer coil is 15.3 Ω so it needs 220 Ω on a GPIO; picking a MOSFET from datasheets for a drone motor (AO3400A fully on at Vgs 2.5 V, 52 mΩ, 0.21 W and ~66 °C at 2 A; IRLZ44N only rated down to Vgs 4 V so not for a 3.3 V GPIO) | [square-wave](day24/square-wave), [tone-check](day24/tone-check), [melody-player](day24/melody-player), [night-light-ldr](day24/night-light-ldr) |
| 25 | Review day: pointers to struct array elements (`Led*` + `&leds[i]`), bit masks as a row of on/off switches (`^=` to toggle, `bitRead()` to read, `Serial.println(x, BIN)`). Project: siren with 3 modes on one button (OFF / BEEP / SIREN) as a state machine; BEEP plays 2000 Hz for 200 ms every 400 ms, SIREN alternates 1500 / 2200 Hz every 300 ms, all with `millis()` so nothing blocks. A green / yellow / red LED blinks to show the current mode. Hardware: buzzer louder from 5 V through an IRLZ44N low-side switch (100 Ω gate resistor, 10k pull-down, 100 Ω in series with the 15.3 Ω coil, ~44 mA measured, 0.19 W on the resistor); loudest near the buzzer's ~2 kHz resonance | [siren-modes](day25/siren-modes) |
| 26 | Project: room alarm with a PIR motion sensor. First a sensor test that prints once when motion starts and ends (edge detection on a level signal: `isMotion != wasMotion`) and how long the HC-SR501 output stays HIGH (~4 s minimum, longer while someone keeps moving). Then a 4-state alarm planned on paper first (state table → one `case` per state, one `if` per event): DISARMED → ARMING (10 s exit delay, yellow blink + chirp every second) → ARMED → ALARM (red blink, 1500/2200 Hz siren; button stops it, and it re-arms by itself after 10 s with no motion, the timer restarting on every movement). Nothing blocks: every wait is a `millis()` check | [pir-test](day26/pir-test), [pir-alarm](projects/pir-alarm) |
| 27–28 | Month 1 review. A tea timer written from a blank page: paper first (what runs once / every pass / only on an event, then a state table), then IDLE → BREWING (30 s, yellow blink, prints the seconds left every second, button cancels) → READY (red LED, 2000 Hz beeps, back to IDLE on the button or after 10 s). Key lesson: a start timestamp is written once; elapsed time is always `now - startTime`. Plus three LEDs blinking at different rates, rewritten from memory with a `struct` array and one `updateLed`-style function that takes a pointer to one LED | [tea-timer](day28/tea-timer), [led-struct-blink](day28/led-struct-blink) |
| 29 | Talking to the board over UART: typing commands in the Serial Monitor. Read only when `Serial.available() > 0` (glance at the mailbox, never wait), `readStringUntil('\n')`, then `trim()` (removes the invisible `\r` that "Both NL & CR" adds) and `toLowerCase()`. An LED that obeys `on` / `off` / `toggle` / `status`, then a 3-mode light (OFF / ON / BLINK) driven by both typed commands and a button: `speed 200` sets the blink interval (50–2000 ms, otherwise an error and the old value is kept), `status` prints the mode and how long it has been in it. A `readCommand()` helper works like `buttonPressed()`, and one `setMode()` does the three things a mode change always needs (set mode, record the start time, print). Hardware: 3.3 V vs 5 V logic levels (VOH/VIH, absolute maximum), why a 5 V HC-SR04 Echo needs a voltage divider before an ESP32 pin | [led-command](day29/led-command), [serial-blinker](day29/serial-blinker) |

## Side projects

- [Ultrasonic distance LEDs](projects/ultrasonic-distance-leds): HC-SR04 sensor turns a red LED on when something is within 10 cm.
- [Ultrasonic distance bar](projects/ultrasonic-distance-bar): a button switches it on/off; blue, green and red LEDs light up like a parking sensor as something gets closer.
- [OLED distance display](projects/oled-distance-display): HC-SR04 + SSD1306 OLED.
- [ESP32 parking sensor](projects/esp32-parking-sensor): ESP32 + HC-SR04 (Echo through a 5V to 3.3V voltage divider) + 3 LEDs + OLED, ON/OFF button, 5-sample moving average that skips failed readings.

- [Traffic light](projects/traffic-light): ESP32 traffic light with a pedestrian button, a pot that sets the green time and a 7-segment countdown. Schematic drawn in KiCad ([PDF](projects/traffic-light/hardware/traffic-light-schematic.pdf)).
- [PIR alarm](projects/pir-alarm): ESP32 room alarm with an HC-SR501 motion sensor, 10 s exit delay, auto re-arm after 10 s without motion, LED status and a 5 V siren driven through a MOSFET. KiCad schematic + PDF in [hardware](projects/pir-alarm/hardware).

## Hardware I use

Arduino UNO, breadboard, red/green/blue 5 mm LEDs, resistors (E12), 10k potentiometer, tactile push button, HC-SR04 ultrasonic sensor, SSD1306 OLED, UNI-T UT890D+ multimeter, ESP32 DevKit, 1-digit and 4-digit 7-segment displays (common cathode). Schematics in KiCad.

## Things I learned the hard way

- Plain global variables never go in a `.h`: every file that includes it gets its own copy, and the linker fails with "multiple definition". `const` values are fine.
- A function prototype in the `.h` must match the body in the `.cpp` exactly. `setLedLevel(int)` and `setLedLevel(float)` are two different functions in C++, so a mismatch gives "undefined reference" from the linker.
- Compile errors ("not declared", "does not name a type") come from one file at a time; linker errors (`ld.exe`, "undefined reference", "multiple definition") only show up when all files are joined.
- `#define` is blind text replacement: `#define LED_PIN 18;` pastes the `;` too. Prefer `const int`.
- Keep sketches outside OneDrive: sync made the editor and the file on disk disagree.
- Inside a function that takes a struct pointer, use `p->field`, not `p.field`.
- A bigger capacitor in an RC filter means less ripple but a slower response (τ = R × C).
- `x % 3` with `x < 3` is just `x`. To cycle 0,1,2,0 write `(mode + 1) % 3`, brackets first.
- A pin that only reacts at the moment a button is pressed never updates again: handle the press and the output in separate blocks.
- `7 / 60` is `0` in C: integer division. Write `7.0 / 60`.
- Global counters keep their value between `loop()` runs, so reset them.
- A button needs **edge detection** (act only when it changes from released to pressed) and a short **debounce** delay.
- A floating input pin reads random values; use `INPUT_PULLUP`.
- LED brightness is not proportional to current; your eyes are a bad meter.
- A variable declared inside `loop()` is created again every pass, so it can't count. Counters live outside.
- A function and a variable can't share the same name.
- A pointer holds an address, not a value: `p` is the address, `*p` is what lives there. A function given a copy (`int x`) can never change the caller's variable; given the address (`int* x`, called with `&value`) it can, which is how one function hands back two results.
- Looping over an array of N items is `i = 0; i < N`. With `<=` the loop reads one slot past the end and gets garbage, with no error.
- `delay()` makes the whole board deaf: a button pressed during a 1.3 s blink is simply missed. `millis()` timing (`now - last >= interval`) never waits.
- Code statements can't sit outside a function, and a `const` can't be changed later, so timestamps are never `const`.
- The ESP32 ADC is 12-bit (0–4095) but not linear: it reads nothing below about 0.14 V and saturates near 3.13 V. `analogReadMilliVolts()` is calibrated and within ~1% in the middle. Use ADC1 pins (32–39); ADC2 stops working when Wi-Fi is on.
- A float is almost never exactly equal to a number, so compare with `>=`, not `==`.
- `constrain(x, low, high)` and `a - b` give back a new value; written alone on a line, the result is thrown away. Write `x = constrain(x, low, high);`.
- `x >> n` divides by 2^n and `x << n` multiplies, on whole numbers only (no `float`). `1 << i` is a mask with one bit set; `&` reads that bit, `^` flips it. A number starting with 0 is octal in C: write binary as `0b0101`.
- Subtracting `unsigned long` values never goes negative: `2000 - 3000` wraps around to about 4.29 billion. Do the subtraction only when you know the first number is bigger (for example, right after the state change, not before).
- Multiply before you divide with whole numbers: `raw * 7000 / 4095` is exact, `raw * (7000 / 4095)` is `raw * 1`.
- Passing an array to a function only passes the address of its first element, so the function can change the real array but has no idea how long it is: pass the count too. `sizeof` inside the function gives 4, the size of an address.
- `(uint32_t)array + i` adds `i` bytes, because the cast turns the address into a plain number first. `(uint32_t)(array + i)` moves `i` elements.
- `%` gives the remainder, not the decimals: `100 / 60 = 1` and `100 % 60 = 40`, so 100 s is 1 min 40 s.
- `tone()` keeps playing on its own; `delay()` after it only decides how long you hear it. The next `tone()` or `noTone()` changes it.
- A MOSFET's Vgs(th) is only where it *starts* to conduct. To know if 3.3 V turns it fully on, look at the lowest Vgs listed next to Rds(on).
- A `String` method like `trim()` changes the string itself and returns nothing (unlike C#'s `s = s.Trim()`). `'a'` is one character, `"a"` is text: `cmd == 'on'` doesn't compile.
- Writing `int x = ...` inside a block makes a brand-new `x` that hides the global one; to change the global, leave out the type.
