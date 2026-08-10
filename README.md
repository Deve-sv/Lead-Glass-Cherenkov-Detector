# Proyecto de Grado — Detector Cherenkov de Cristal de Plomo

## Descripción

Este repositorio contiene el desarrollo de mi proyecto de grado, centrado en la **simulación y análisis de la respuesta de un fotomultiplicador (PMT) asociado a un detector Cherenkov de cristal de plomo**.

El objetivo principal del proyecto es **analizar y caracterizar la señal producida por el PMT** a partir de eventos simulados, estudiando la relación entre las partículas que atraviesan el detector, los fotones Cherenkov producidos y la señal finalmente observada por el fotomultiplicador.

El proyecto combina **simulación de física de partículas, procesamiento de datos y análisis científico**, utilizando principalmente Geant4, ROOT y Python.

---

## Objetivos

Los principales objetivos del proyecto son:

* Simular la interacción de partículas con un detector Cherenkov de cristal de plomo.
* Estudiar la producción y propagación de fotones Cherenkov dentro del detector.
* Modelar la detección de fotones mediante un fotomultiplicador (PMT).
* Analizar los tiempos de llegada y las características de los fotones detectados.
* Reconstruir la señal temporal producida por el PMT.
* Estudiar la respuesta del PMT ante los eventos simulados.
* Reconstruir y analizar el espectro de energía de los electrones de Michel.
* Caracterizar las propiedades de la señal obtenida.

---

## Simulación del detector

La simulación se desarrolla utilizando **[Geant4](https://geant4.web.cern.ch/)**, un framework utilizado para simular el transporte e interacción de partículas con la materia.

El detector está basado en un **cristal de plomo** con propiedades ópticas adecuadas para la producción y propagación de radiación Cherenkov.

Dentro de la simulación se consideran procesos físicos relevantes como:

* Producción de radiación Cherenkov.
* Absorción de fotones.
* Dispersión Rayleigh.
* Reflexión en las superficies del detector.
* Transporte óptico de los fotones.
* Detección de fotones por el PMT.

El objetivo es obtener información detallada de cada evento, incluyendo las partículas involucradas y los fotones que alcanzan la superficie de detección.

---

## Muones y electrones de Michel

Una parte fundamental de la simulación consiste en estudiar **muones que atraviesan el detector y posteriormente se desintegran**.

El proceso de interés es:

$$
\mu^- \rightarrow e^- + \nu_\mu + \bar{\nu}_e
$$

El electrón producido en esta desintegración se conoce como **electrón de Michel**.

La energía de estos electrones sigue una distribución característica, conocida como **espectro de Michel**.

El objetivo del análisis es estudiar cómo esta distribución física se transforma en una señal observable después de pasar por:

$$
\text{Partícula}
\rightarrow
\text{Cristal Cherenkov}
\rightarrow
\text{Fotones}
\rightarrow
\text{PMT}
\rightarrow
\text{Señal eléctrica}
$$

---

## Fotomultiplicador

El detector utiliza como referencia un **Hamamatsu R1512**, utilizado para convertir los fotones Cherenkov detectados en una señal eléctrica.

La simulación y el análisis consideran las características relevantes del PMT, incluyendo:

* Eficiencia cuántica.
* Ganancia.
* Tiempo de tránsito.
* Tiempo de subida.
* Respuesta temporal.
* Carga asociada a un fotoelectrón.

A partir de los fotones detectados se construye una representación de la señal temporal producida por el PMT.

---

## Análisis de datos

Los datos generados por Geant4 son almacenados y posteriormente procesados para extraer las variables relevantes de cada evento.

El análisis combina **ROOT** y **Python**, utilizando herramientas como:

* NumPy
* Pandas
* Matplotlib
* SciPy
* Uproot
* Awkward Array
* ROOT

El flujo general de análisis es:

```text
Geant4
   │
   ▼
Simulación de eventos
   │
   ▼
Producción y transporte de fotones
   │
   ▼
Fotones detectados por el PMT
   │
   ▼
Extracción de datos
   │
   ├── ROOT
   └── Python
          │
          ▼
   Procesamiento de datos
          │
          ▼
   Análisis temporal
          │
          ▼
   Reconstrucción de la señal
          │
          ▼
   Caracterización del PMT
```

---

## Reconstrucción de la señal

Uno de los pasos principales del análisis consiste en transformar la información de los fotones detectados en una señal temporal representativa del PMT.

Para ello se estudian los tiempos de llegada de los fotones y se identifican las diferentes contribuciones temporales correspondientes a los eventos simulados.

Posteriormente, se utiliza una respuesta de **Single Photoelectron (SPE)** para modelar la contribución individual de los fotoelectrones.

La señal total puede representarse conceptualmente como la convolución entre la distribución temporal de los fotones detectados y la respuesta del PMT:

$$
S(t) = N_{\gamma}(t) * R_{\mathrm{SPE}}(t)
$$

donde:

- $N_{\gamma}(t)$ representa la distribución temporal de fotones detectados.
- $R_{\mathrm{SPE}}(t)$ representa la respuesta del PMT a un fotoelectrón.
- $S(t)$ representa la señal reconstruida.
Este procedimiento permite pasar de información discreta de fotones a una señal temporal continua que puede ser analizada.

---

## Resultados

El resultado principal del proyecto es la **caracterización de la señal producida por el PMT** a partir de los eventos simulados.

El análisis permite estudiar cómo las características del evento físico y de los fotones producidos en el cristal se reflejan en la señal final del fotomultiplicador.

Entre las variables analizadas se encuentran:

* Número de fotones detectados.
* Distribución temporal de los fotones.
* Número de fotoelectrones.
* Forma temporal de la señal.
* Carga integrada de la señal.
* Respuesta del PMT.
* Relación entre la energía depositada y la señal obtenida.

---

## Tecnologías utilizadas

| Tecnología        | Uso                                                   |
| ----------------- | ----------------------------------------------------- |
| **C++**           | Desarrollo de la simulación                           |
| **Geant4**        | Simulación del transporte e interacción de partículas |
| **ROOT**          | Almacenamiento y análisis de datos                    |
| **Python**        | Procesamiento y análisis científico                   |
| **NumPy**         | Cálculo numérico                                      |
| **Pandas**        | Manipulación de datos                                 |
| **Matplotlib**    | Visualización                                         |
| **SciPy**         | Procesamiento y análisis numérico                     |
| **Uproot**        | Lectura de archivos ROOT desde Python                 |
| **Awkward Array** | Manipulación de datos estructurados de eventos        |

---

## Estructura del proyecto

```text
Proyecto-de-grado---cristal-de-plomo/
│
├── Crystalg4/
   └── Código de simulación Geant4
      │
      ├── analysis/
      │   └── Scripts de análisis en Python
      │
      ├── data/
      │   └── Datos generados por las simulaciones
      │
      ├── results/
      │   └── Gráficos y resultados del análisis
      │
├── README.md
└── ...
```

> La estructura anterior puede adaptarse a la organización definitiva del repositorio.

---

## Motivación

Este proyecto integra diferentes áreas de la física computacional y el análisis de datos:

**Física de partículas → Simulación Monte Carlo → Generación de datos → Procesamiento → Análisis estadístico → Reconstrucción de señales**

Además de estudiar el comportamiento físico del detector, el proyecto proporciona un flujo completo de trabajo con datos científicos simulados, desde su generación hasta la extracción de información física.

---

## Autor

**Sergio Villalba**

Proyecto de grado — Física

### Áreas de interés

* Data Science
* Scientific Computing
* Machine Learning
* Física de partículas
* Simulación Monte Carlo
* Análisis de datos científicos
* Detectores de partículas
