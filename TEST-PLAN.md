# Test plan

Fill this document only with tests actually performed.

## Pre-test checks
- [ ] Confirm wiring against the physical circuit.
- [ ] Confirm module voltage requirements.
- [ ] Check LED series resistors.
- [ ] Confirm LCD I2C address.
- [ ] Install required Arduino libraries.
- [ ] Allow the MQ-135 module to warm up as specified by its manufacturer.
- [ ] Keep tests controlled and do not expose people to hazardous gases.

## Test record

| Test ID | Test condition | MQ-135 raw ADC | Temperature (°C) | Humidity (%) | LED state | Observation |
|---|---|---:|---:|---:|---|---|
| T01 | Baseline/clean-air observation | To measure | To measure | To measure | To record | To record |
| T02 | Controlled sensor response test | To measure | To measure | To measure | To record | To record |
| T03 | Repeatability test | To measure | To measure | To measure | To record | To record |

Do not use unknown or hazardous gases for informal testing. Use suitable controlled test methods and reference instruments under qualified supervision.

## Acceptance observations
Describe whether the LCD updates, sensor values are read, and the LEDs respond to the configured demonstration threshold. This is a functional prototype check, not safety certification.
