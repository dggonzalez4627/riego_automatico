# Componentes

## Lista de materiales

- 1 Arduino UNO.
- 1 LCD 16x2 paralelo compatible con HD44780.
- 1 potenciometro de 10 k para contraste de LCD.
- 1 potenciometro adicional para simular humedad, o 1 sensor analogico de humedad de tierra.
- 1 modulo rele de 5 V.
- 1 pulsador.
- 1 resistencia de 220 ohm para la luz de fondo de la LCD.
- Cables jumper.
- Protoboard.
- Fuente adecuada para la bomba.

## Librerias

El proyecto usa la libreria incluida con Arduino IDE:

```cpp
#include <LiquidCrystal.h>
```

No necesitas instalar librerias externas.

## Recomendaciones electricas

- No alimentes una bomba directamente desde el pin del Arduino.
- Si la bomba consume mas corriente que la disponible por USB, usa una fuente externa.
- Une el GND del Arduino con el GND del modulo rele si el modulo lo requiere.
- Revisa si tu modulo rele es activo en bajo o activo en alto.
- Si controlas cargas de alto voltaje, usa caja, aislamiento y conexiones seguras.
