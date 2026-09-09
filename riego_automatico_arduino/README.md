# Riego automatico con Arduino UNO

Proyecto de prueba para controlar una bomba de agua con Arduino UNO, una pantalla LCD 16x2, un potenciometro o sensor de humedad de tierra, un rele y un pulsador.

El sistema muestra la humedad en la pantalla con el formato:

```text
Humedad x% RH
```

Tambien envia los valores por el monitor serial y controla el rele de forma automatica o manual.

## Funciones

- Lectura analogica desde `A0`.
- Visualizacion de humedad en LCD 16x2.
- Salida digital para rele en `D8`.
- Control automatico por humedad.
- Pulsador en `D7` con resistencia interna `INPUT_PULLUP`.
- Mientras el pulsador esta oprimido, la bomba se activa.
- Doble pulsacion rapida para dejar la bomba fija encendida.
- Nueva doble pulsacion rapida para apagar el modo fijo.
- Monitor serial a `9600 baudios`.

## Hardware usado

- Arduino UNO.
- LCD 16x2 paralelo compatible con HD44780.
- Potenciometro para simular humedad, o sensor analogico de humedad de tierra.
- Modulo rele de 5 V.
- Pulsador.
- Potenciometro de 10 k para contraste de LCD.
- Resistencia de 220 ohm para la luz de fondo de la LCD.
- Cables jumper y protoboard.

## Pines

| Elemento | Pin Arduino |
| --- | --- |
| Sensor/potenciometro | `A0` |
| Rele | `D8` |
| Pulsador | `D7` |
| LCD RS | `D12` |
| LCD E | `D11` |
| LCD D4 | `D5` |
| LCD D5 | `D4` |
| LCD D6 | `D3` |
| LCD D7 | `D2` |

## Uso

1. Abre `riego_automatico_arduino.ino` en Arduino IDE.
2. Selecciona la placa `Arduino UNO`.
3. Selecciona el puerto correspondiente.
4. Sube el programa.
5. Abre el monitor serial a `9600 baudios`.

## Umbrales

El rele se activa automaticamente si la humedad baja o llega a:

```cpp
const int humedadEncenderBomba = 35;
```

El rele se apaga automaticamente si la humedad sube o llega a:

```cpp
const int humedadApagarBomba = 55;
```

Estos dos valores crean una zona de seguridad para evitar que el rele este prendiendo y apagando demasiado rapido.

## Documentacion

- [Conexiones](docs/conexiones.md)
- [Calibracion](docs/calibracion.md)
- [Componentes](docs/componentes.md)

## Nota de seguridad

Si la bomba trabaja con voltaje externo o corriente alta, no la conectes directamente al Arduino. Usa un modulo rele adecuado, fuente externa para la bomba y aislamiento electrico correcto.
