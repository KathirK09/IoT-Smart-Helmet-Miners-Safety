# Example connection guide — verify before wiring

This is a proposed pin map for the starter sketch, not confirmation of your actual circuit.

| Device | Pin | Arduino Uno |
|---|---|---|
| MQ-135 | AO | A0 |
| MQ-135 | VCC/GND | Follow module datasheet; common modules accept 5 V |
| DHT11 | DATA | D2 |
| DHT11 | VCC/GND | Follow sensor/module datasheet |
| I2C LCD | SDA | A4 |
| I2C LCD | SCL | A5 |
| I2C LCD | VCC/GND | Follow LCD backpack requirements |
| Green LED | Anode through resistor | D9 |
| Red LED | Anode through resistor | D8 |
| LEDs | Cathode | GND |

## Wiring checks
- Use a current-limiting resistor in series with each LED (for example, 220–330 ohms).
- Connect all grounds together.
- Check the MQ-135 module's pin labels: use **AO** for the analogue input in this sketch.
- The LCD address may be `0x27` or `0x3F`; confirm it using an I2C scanner.
- Some bare DHT11 sensors need a pull-up resistor; many breakout modules already include one.
- Verify supply voltage and pinout from the exact module datasheets.
- Disconnect power before changing wiring.
