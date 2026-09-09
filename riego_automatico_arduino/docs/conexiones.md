# Conexiones

## LCD 16x2 a Arduino UNO

La pantalla se usa en modo paralelo de 4 bits.

| Pin LCD | Nombre | Conexion |
| --- | --- | --- |
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | V0 | Pin central de potenciometro de contraste de 10 k |
| 4 | RS | Arduino D12 |
| 5 | RW | GND |
| 6 | E | Arduino D11 |
| 7 | D0 | Sin conectar |
| 8 | D1 | Sin conectar |
| 9 | D2 | Sin conectar |
| 10 | D3 | Sin conectar |
| 11 | D4 | Arduino D5 |
| 12 | D5 | Arduino D4 |
| 13 | D6 | Arduino D3 |
| 14 | D7 | Arduino D2 |
| 15 | A | 5V con resistencia de 220 ohm |
| 16 | K | GND |

## Potenciometro para simular humedad

| Pin del potenciometro | Conexion |
| --- | --- |
| Extremo 1 | 5V |
| Pin central | Arduino A0 |
| Extremo 2 | GND |

## Sensor de humedad de tierra

Cuando reemplaces el potenciometro por el sensor real:

| Pin del sensor | Conexion |
| --- | --- |
| VCC | 5V |
| GND | GND |
| AO / Analog Out | Arduino A0 |

Usa la salida analogica del sensor, no la salida digital, para poder ver el porcentaje.

## Rele

| Pin del rele | Conexion |
| --- | --- |
| IN | Arduino D8 |
| VCC | 5V |
| GND | GND |

Muchos modulos de rele son activos en bajo. El codigo viene configurado para ese caso:

```cpp
const bool releActivoEnBajo = true;
```

Si tu rele funciona al contrario, cambia a:

```cpp
const bool releActivoEnBajo = false;
```

## Pulsador

| Pin del pulsador | Conexion |
| --- | --- |
| Pin 1 | Arduino D7 |
| Pin 2 | GND |

No se necesita resistencia externa porque el programa usa:

```cpp
pinMode(botonPin, INPUT_PULLUP);
```
