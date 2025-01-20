# ESP32 + Modbus RS-485 + CWT-Soil-THC-S (Soil Sensor)

## Project Overview
This project demonstrates the use of the **Modbus RTU protocol** over RS-485 communication using an ESP32 microcontroller. It reads sensor data, including humidity, temperature, conductivity, salinity, and TDS (Total Dissolved Solids), from Modbus registers and outputs the results via serial communication.

---

## Key Features
- **Modbus RTU Communication:**
  - Implements ModbusMaster library for RS-485 communication.
  - Configures pre-transmission and post-transmission modes for seamless data flow.

- **Parameter Reading:**
  - Reads specific holding registers to fetch sensor values.
  - Applies a conversion factor for proper data representation.

- **RS-485 Control:**
  - Uses MAX3485 transceiver with RE and DE pins controlled by GPIO 4.

---

## Hardware Requirements
- **ESP32 Development Board**
- **MAX3485 RS-485 Transceiver**
  - RE/DE Pin: GPIO 4 (shared for enabling transmission/reception).
  - TX Pin: GPIO 16
  - RX Pin: GPIO 17
- **RS-485 Bus with Modbus Sensors**

---

## Workflow
1. **Initialization:**
   - Configures the RE/DE pin to control transmission and reception modes.
   - Initializes the Modbus RTU connection with the device address set to `1`.
   - Begins serial communication for debugging.

2. **Parameter Reading:**
   - Continuously reads sensor data from specific holding registers.
   - Converts raw register values into meaningful data using predefined factors.

3. **Error Handling:**
   - Displays error codes if communication with the Modbus device fails.

---

## Modbus Register Map
- **0x0000:** Humidity (%RH, scaled by 0.1)
- **0x0001:** Temperature (°C, scaled by 0.1)
- **0x0002:** Conductivity (units, no scaling)
- **0x0003:** Salinity (units, no scaling)
- **0x0004:** TDS (units, no scaling)

---

## Configuration
- **Baud Rate:** 4800 bps
- **Serial Configuration:** 8 data bits, no parity, 1 stop bit (SERIAL_8N1)
- **Device Address:** 1 (default in code, configurable in Modbus).
- **RE/DE Pin Control:** Shared GPIO 4 to toggle between transmission and reception.

---

## Requirements
- **Arduino IDE or PlatformIO**
- Libraries:
  - `ModbusMaster.h`
  - `Wire.h` (for I2C devices, not used in this code but common dependency)
- Properly wired RS-485 hardware with sensors supporting Modbus RTU.

---

## Usage
1. Connect the RS-485 transceiver to the ESP32.
2. Wire sensors or devices to the RS-485 bus.
3. Upload the code to the ESP32 using Arduino IDE or PlatformIO.
4. Monitor the serial output for sensor readings and error messages.

---

## Example Log Output
```
Humidity: 55.2
Temperature: 24.5
Conductivity: 400
Salinity: 35
TDS: 500
```

In case of errors:
```
Error reading Humidity: 2
Error reading Temperature: 3
```

---

## Notes
- Ensure all devices on the RS-485 bus share the same baud rate and communication settings.
- Address conflicts can cause errors. Ensure each Modbus device has a unique address.
- Use proper termination resistors on the RS-485 bus to avoid communication issues.

---
