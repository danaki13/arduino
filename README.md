# Personal Arduino projects

Collection of projects based on Aurdino hardware

## Measure Resistance

This code used with Arduino UNO and the circuit shown in below figure will allow the user to measure resistance values (by replacing R2) and print it's values to the Serial Monitor.
R<sub>ref</sub> should be chosen according to what resistor is expected to be measured. This was tested with R<sub>ref</sub> = 220 $\Omega$ and measured R<sub>2</sub> = 220...10 $k\Omega$.

```math
V_A = \frac{V_{ref}}{R_{ref} + R_2} * R_2 => R_2 = \frac{R_{ref}\frac{V_A}{V_{ref}}}{1-\frac{V_A}{V_{ref}}}
```

![alt text](https://github.com/danaki13/arduino/blob/main/artwork/measure_resistor.png?raw=true)
