# Calibracion

## Prueba con potenciometro

El codigo convierte la lectura analogica de `A0` a porcentaje usando:

```cpp
int humedad = map(lectura, 0, 1023, 0, 100);
```

Con esta configuracion:

- `0` equivale a `0%`.
- `1023` equivale a `100%`.

Puedes revisar los valores en el monitor serial a `9600 baudios`.

## Uso con sensor real de humedad

Cuando uses un sensor de humedad de tierra analogico, puede ocurrir que la lectura quede invertida. Si al meter el sensor en tierra humeda el porcentaje baja en lugar de subir, cambia esta linea:

```cpp
int humedad = map(lectura, 0, 1023, 0, 100);
```

por esta:

```cpp
int humedad = map(lectura, 0, 1023, 100, 0);
```

## Ajuste recomendado

Para calibrar mejor el sensor real:

1. Mide el valor analogico con el sensor en tierra seca.
2. Mide el valor analogico con el sensor en tierra humeda.
3. Reemplaza los valores `0` y `1023` de la funcion `map()` por tus mediciones reales.

Ejemplo:

```cpp
int humedad = map(lectura, 850, 300, 0, 100);
```

En ese ejemplo:

- `850` seria tierra seca.
- `300` seria tierra humeda.

## Umbrales de bomba

El control automatico usa dos umbrales:

```cpp
const int humedadEncenderBomba = 35;
const int humedadApagarBomba = 55;
```

La bomba se enciende cuando la humedad esta en `35%` o menos.

La bomba se apaga cuando la humedad esta en `55%` o mas.

Este margen evita cambios rapidos del rele cuando la lectura esta cerca del limite.
