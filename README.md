# ChaosPRNG

Implementación en C de un generador de números pseudoaleatorios (PRNG) basado en mapas caóticos y un registro de desplazamiento con retroalimentación lineal (LFSR), según el diseño descrito en:

> **"An efficient chaos pseudo-random number generator applied to video encryption"**
> Hui Xu, Xiaojun Tong, Xianwen Meng
> *Optik, Vol. 127, pp. 9305–9319, 2016*
> https://doi.org/10.1016/j.ijleo.2016.07.024

---

## Descripción

El PRNG combina tres componentes para generar secuencias pseudoaleatorias de alta calidad:

- **LFSR de 16 etapas**: Registro de desplazamiento con retroalimentación lineal. Cada celda almacena un entero de 31 bits. Opera en modo inicialización (recibe entrada externa) y modo trabajo (autónomo).
- **Reorganización de bits (BR)**: Extrae y reordena bits del LFSR para formar cuatro palabras de 32 bits (X0, X1, X2, X3).
- **Función no lineal F**: Combina las palabras reorganizadas con dos registros de memoria (R1, R2) y dos mapas caóticos:
  - **F1**: `x(n) = 2·x(n-1)² - 1`, operando en el intervalo `[-1, 1]`
  - **F2**: `y(n) = 4·y(n-1)³ - 3·y(n-1)`, operando en el intervalo `[-1, 1]`

La salida de cada iteración es una palabra Z de 32 bits. Tal y como especifica el paper, se descartan los primeros 100 valores generados antes de usar la salida.

---

## Estructura del proyecto

```
ChaosPRNG/
├── ChaosPRNG.c       # Implementación del PRNG (init, next, F, F1, F2, BR)
├── ChaosPRNG.h       # Definición de la estructura de contexto y la API pública
├── main.c            # Punto de entrada: lee semillas, genera números y los guarda
├── utils.c           # Lectura de semillas desde archivo de texto
├── utils.h           # Cabecera de utilidades
├── seeds             # Archivo de semillas de ejemplo
├── Python Tests/
│   ├── Bin_test.py   # Análisis visual de la salida binaria (mapa de bits y frecuencias)
│   ├── F1_test.py    # Análisis del mapa caótico F1 (sensibilidad e diagrama de telaraña)
│   └── F2_test.py    # Análisis del mapa caótico F2 (sensibilidad e diagrama de telaraña)
└── ChaosPRNG.sln     # Solución de Visual Studio
```

---

## Compilación

### Visual Studio (Windows)
Abre `ChaosPRNG.sln` y compila en modo Release o Debug.

### GCC (Linux/macOS)
```bash
gcc -O2 -o ChaosPRNG main.c ChaosPRNG.c utils.c -lm
```

---

## Uso

```
ChaosPRNG.exe <semillas.txt> <cantidad> <salida> <formato>
```

| Parámetro    | Descripción                                              |
|-------------|----------------------------------------------------------|
| `semillas.txt` | Archivo de texto con las semillas del PRNG            |
| `cantidad`   | Número de valores pseudoaleatorios a generar             |
| `salida`     | Ruta del archivo de salida                               |
| `formato`    | `TXT` para texto plano, `BIN` para binario               |

### Ejemplo

```bash
# Generar 1000000 números en formato binario
ChaosPRNG.exe seeds 1000000 out.bin BIN

# Generar 10000 números en formato texto
ChaosPRNG.exe seeds 10000 out.txt TXT
```

---

## Formato del archivo de semillas

```
[s0, s1, s2, ..., s15]
R1 = <valor>
R2 = <valor>
x = <valor>
y = <valor>
```

- `s0`–`s15`: 16 enteros sin signo de 31 bits (estado inicial del LFSR).
- `R1`, `R2`: Enteros de 32 bits para los registros de la función no lineal F.
- `x`, `y`: Valores reales en el intervalo `(-1, 1)` como semillas de los mapas caóticos F1 y F2.

### Ejemplo de archivo de semillas

```
[123456789, 987654321, 111111111, 222222222, 333333333, 444444444, 555555555, 666666666, 777777777, 888888888, 999999999, 100000001, 200000002, 300000003, 400000004, 500000005]
R1 = 1234567890
R2 = 9876543210
x = 0.6444243540
y = 0.4461243550
```

---

## Tests en Python

Los scripts de `Python Tests/` permiten analizar visualmente las propiedades estadísticas del generador.

### `Bin_test.py` — Análisis de la salida binaria

Lee el archivo `.bin` generado y produce:
- **Mapa de bits**: representación visual de la secuencia de bits.
- **Frecuencia de ceros y unos**: contraste con la distribución ideal 50/50.

```bash
python "Python Tests/Bin_test.py"
```
> Edita la variable `archivo_bin` en el script para apuntar a tu archivo de salida.

### `F1_test.py` — Análisis del mapa caótico F1

Visualiza las propiedades caóticas de `F1(x) = 2x² - 1`:
- **Sensibilidad a condiciones iniciales** (efecto mariposa).
- **Diagrama de telaraña** (cobweb).

```bash
python "Python Tests/F1_test.py"
```

### `F2_test.py` — Análisis del mapa caótico F2

Visualiza las propiedades caóticas de `F2(y) = 4y³ - 3y`:
- **Sensibilidad a condiciones iniciales**.
- **Diagrama de telaraña**.

```bash
python "Python Tests/F2_test.py"
```

**Dependencias Python:**
```bash
pip install numpy matplotlib
```

---

## Espacio de clave

Tal como se describe en el paper, el espacio de clave es:

```
2^(16×31 + 2×32) × (2×2^32)² = 2^626
```

Suficientemente grande para resistir ataques de fuerza bruta.

---

## Referencia

```bibtex
@article{xu2016efficient,
  title={An efficient chaos pseudo-random number generator applied to video encryption},
  author={Xu, Hui and Tong, Xiaojun and Meng, Xianwen},
  journal={Optik},
  volume={127},
  number={19},
  pages={9305--9319},
  year={2016},
  publisher={Elsevier},
  doi={10.1016/j.ijleo.2016.07.024}
}
```
