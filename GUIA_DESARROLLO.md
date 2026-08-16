# Guía de desarrollo — Tycoon Air (Airplane)

> Documento orientativo, no de soluciones. Está pensado para que avances tú
> mismo, en tu orden, apoyándote en preguntas y checklists en lugar de código
> ya hecho. Actualízalo o táchalo a medida que avances: es tuyo.

## 0. Cómo usar esta guía

- No es un tutorial paso a paso con código para copiar. Es un mapa: te dice
  **qué falta**, **en qué orden tiene sentido abordarlo** y **qué preguntas
  hacerte** antes de dar por terminada cada pieza.
- Cada fase incluye una sección "Antes de pasar a la siguiente fase,
  pregúntate..." — tómatelas en serio. Si no sabes responderlas, ese es el
  siguiente sitio donde investigar o escribir una prueba, no adivinar.
- Cuando pidas ayuda (a mí o a quien sea) durante el desarrollo, pide
  **revisión** ("¿ves algún problema en esta función?") en vez de
  **solución** ("hazme esta función"). Aprenderás el doble en la mitad de
  tiempo.

## 1. Fotografía del proyecto actual

Estructura:

```
Airplane/
├── Includes/        <- interfaces públicas (.h), un módulo por fichero
│   ├── types.h       Position, Status, Bool, Id, Level
│   ├── city.h         City (opaco)
│   ├── plane.h         Plane (opaco)
│   ├── route.h          Route (opaco)
│   └── game.h             Game (opaco)
├── Src/              <- implementación (.c), misma organización
├── main.c            <- menú inicial + arranque de partida
└── Makefile
```

Estado real de cada módulo ahora mismo (léelo con espíritu crítico, no lo
des por cerrado solo porque "compila"):

| Módulo | Estado | Notas |
|---|---|---|
| `types` | Completo | `Position` con creación, validación y distancia. |
| `city` | Implementado, **sin verificar** | Compila, pero antes de construir nada encima merece una revisión seria (ver Fase 2). |
| `plane` | Completo y documentado | Buen ejemplo de estilo a imitar (Doxygen, nombres, manejo de `NULL`). |
| `route` | Completo y documentado | Igual que `plane`: es tu mejor referencia de estilo en el repo. |
| `game` | Parcial | La estructura y la gestión de rutas/aviones existen; el ciclo de días y la gestión de ciudades **no están terminados**. |
| `main` | Esqueleto | Hay menú de dificultad y arranque de partida, pero no hay bucle de juego después de eso. |

## 2. Mapa de dependencias entre módulos

```
types  ──> city   ──┐
types  ──> plane  ──┼──> route ──> game ──> main
```

Regla general que ya sigue el proyecto: un módulo solo incluye los headers
de los módulos de los que depende conceptualmente (`route.h` incluye
`city.h` y `plane.h`, `game.h` incluye los tres). Mantén esa dirección
única: `city` no debería necesitar saber nada de `route`, por ejemplo. Si en
algún momento sientes que un módulo "de abajo" necesita llamar a uno "de
arriba", es señal de que el diseño necesita repensarse, no de que toca
saltarse la regla.

## 3. Convenciones que ya sigue el proyecto (síguelas)

Antes de escribir código nuevo, identifica estos patrones ya presentes y
reutilízalos en vez de inventar otros distintos:

- **Puntero opaco**: en el `.h` solo hay `typedef struct _X X;`; el `struct`
  real vive únicamente en el `.c`. Así el resto del programa no puede tocar
  los campos directamente, solo a través de funciones. ¿Por qué crees que
  interesa eso en un proyecto que va a crecer?
- **`Status` como valor de retorno** (`OK` / `ERROR`) para funciones que
  pueden fallar, y valores centinela (`NO_ID`, `NO_LEVEL`, `-1`) para los
  getters cuando el argumento es inválido.
- **Un `_new`/`_create` con su `_delete`/`_destroy` correspondiente**, y el
  segundo siempre libera todo lo que el primero reservó (incluyendo lo que
  contiene, si aplica — mira `route_destroy` liberando cada avión).
  Repasa la memoria reservada en `game_create`: ¿en `game_destroy` se libera
  exactamente lo mismo, ni más ni menos?
- **Funciones privadas** con guion bajo delante (`_route_max_planes`,
  `_game_is_weekend`) declaradas solo dentro del `.c`, nunca en el `.h`.
- **Comentarios estilo Doxygen** (`@brief`, `@param`, `@return`) en
  `plane.c` y `route.c`. `city.c` y `game.c` no los tienen todavía — sería
  buen momento para uniformar el estilo cuando los toques.

## 4. Hoja de ruta por fases

### Fase 0 — Entorno y control de versiones

- [ ] Comprueba que `make` compila limpio (`make clean && make`) sin avisos
      de `-Wall -Wextra`. Un warning no es "solo un aviso": es el compilador
      diciéndote dónde probablemente vas a tener un bug.
- [ ] Ahora mismo `git status` te va a enseñar binarios y `.o` sin trackear
      (`airplane`, `main.o`, `Src/*.o`) y cambios pendientes en `game.c` y
      `main.c`. Decide qué hacer con eso antes de seguir: ¿esos artefactos
      de compilación deberían estar en el repo? Revisa qué cubre tu
      `.gitignore` actual (es la plantilla genérica de Visual Studio, no
      está pensada para este proyecto en C con `make`).
- [ ] Adopta el hábito de commits pequeños por función/comportamiento
      terminado, como ya vienes haciendo (mira tu propio historial con
      `git log --oneline`, es un buen ejemplo a seguir).

### Fase 1 — `types`: repaso rápido

Este módulo ya está completo, pero es la base de todo lo demás, así que
antes de continuar asegúrate de que lo entiendes del todo:

- ¿Por qué `position_is_valid` usa `NO_POS` como umbral en vez de comprobar
  contra coordenadas negativas cualesquiera?
- ¿Qué pasa si llamas a `position_distance` con una posición inválida?
  Compruébalo leyendo el código, no ejecutando — ¿coincide con lo que
  esperabas?

### Fase 2 — `city`: audita antes de construir encima

Esta es la fase donde más vale la pena parar y **probar en profundidad**
antes de seguir. `city.c` compila, pero antes de que `game` dependa de él
en serio, escribe un pequeño programa de prueba (puede ser un `main`
temporal aparte, o una carpeta `Tests/`) que:

- [ ] Cree una ciudad con un nombre conocido y luego recupere/imprima ese
      nombre. ¿El resultado es el que esperabas? Presta atención especial a
      `word_cpy`: ¿qué se supone que debe hacer una función con ese nombre?
      ¿Lo hace?
- [ ] Pruebe `city_create` con un nombre válido y datos correctos. ¿Devuelve
      lo que esperarías, o devuelve `NULL` en un caso que debería tener
      éxito? Sigue la lógica de la comprobación tras `word_cpy` línea a
      línea.
- [ ] Pruebe casos límite: `name == NULL`, `pop_init` negativo, una
      `Position` inválida, población en 0.
- [ ] Compile con `-fsanitize=address` (ver sección 6) y ejecute esas
      pruebas. ¿Se queja de algo?

No pases a `game` dando `city` por bueno solo porque "no ha crasheado
todavía". Escribir estas pruebas ahora te ahorra horas de depuración más
adelante, cuando el bug esté enterrado tres llamadas más abajo.

### Fase 3 — `plane` y `route`: estudiar, no reescribir

Ambos módulos están terminados y son el mejor ejemplo de estilo del
proyecto. En vez de tocarlos, dedica tiempo a **leerlos como si fueran la
documentación del proyecto**:

- Fíjate en cómo `route` gestiona un array dinámico de punteros
  (`route->planes`) con `realloc`: crecimiento de a uno en uno, manejo del
  caso en que `realloc` falla (¿qué pasa con la memoria ya reservada de
  `n_plane` en ese caso?), actualización del contador solo al final.
  Vas a necesitar exactamente este patrón en `game` para `cities`,
  `routes` y `planes`.
- Fíjate en cómo separan "cálculo puro" (`_route_upgrade_cost`,
  `_route_max_planes`) de la función pública que decide si aplicarlo. Esa
  separación es la que te va a hacer fácil ajustar el balance del juego
  (subir/bajar constantes) sin tocar la lógica.
- Anota qué preguntas te surgen leyéndolos — son buena materia para pedirme
  una revisión conceptual si algo no te cuadra, sin que yo te dé código.

### Fase 4 — `game`: el cerebro de la partida

Esta es la fase central que falta. Dos huecos concretos que ya puedes ver
en el código actual:

**1. No hay forma de añadir ciudades a la partida.**
`game_build_route` necesita dos `City*` ya creados, pero `game.h` no
expone ninguna función tipo `game_add_city` o similar. Piensa:

- ¿Quién debería ser el dueño de las ciudades — el `Game`, o quien llama a
  `game_build_route`? Fíjate en cómo se responde esa misma pregunta para
  `routes` en `game_destroy` y sé consistente.
- ¿Con qué datos necesitas crear una ciudad desde `game` (nombre,
  población inicial, posición)? ¿De dónde deberían salir esos datos —
  ¿del propio jugador, de una lista fija de ciudades iniciales, de
  aleatoriedad?

**2. `game_next_day` no hace nada todavía.**
Ya tienes definidas (aunque sin usar) `_game_is_weekend`,
`_game_day_on_week` y `_game_name_day`. Pregúntate:

- ¿Qué debería ocurrir cada día en un juego de gestión de aerolíneas?
  Piensa en ingresos por pasajeros transportados, crecimiento o descenso de
  población en las ciudades, quizá costes de mantenimiento de rutas o
  aviones.
- ¿Por qué crees que ya existe una distinción entre día laborable y fin de
  semana? ¿Qué differencia de comportamiento tendría sentido introducir ahí
  (más o menos pasajeros, por ejemplo)?
- ¿Dónde encaja `cash` en todo esto? Ahora mismo solo se toca en
  `game_upgrade_route`.

Checklist de la fase:

- [ ] Diseña e implementa la gestión de ciudades en `game` (crear, listar,
      destruir junto con el `Game`).
- [ ] Da contenido real a `game_next_day` (avance de día, y al menos un
      efecto económico o de población).
- [ ] Decide y documenta (con un comentario breve si hace falta) qué
      relación hay entre transportar pasajeros y ganar dinero — es el
      corazón del "tycoon".
- [ ] Repasa `game_destroy`: cuando añadas ciudades, ¿las estás liberando
      ahí también?

### Fase 5 — `main`: el bucle de juego interactivo

Ahora mismo el programa muestra el menú de dificultad, crea la partida...
y termina. Con lo que ya expone `game.h` (construir ruta, comprar avión,
subir de nivel ruta/avión, avanzar día), ¿qué te falta para un bucle
interactivo típico de este tipo de juegos?

- [ ] Un menú de acciones dentro de la partida (no el de dificultad, uno
      nuevo) que se repita hasta que el jugador decida salir.
- [ ] Alguna forma de que el jugador vea el estado actual antes de decidir
      (efectivo, ciudades, rutas) — ¿qué getters te faltan en `game.h` para
      poder mostrar eso? (Fíjate: ahora mismo `game.h` no expone ni el
      efectivo ni el día actual hacia fuera. ¿Cómo lo resolverías sin rompe
      el patrón de puntero opaco?)
- [ ] Manejo de entrada robusto: ya tienes en `menu_main` un patrón de
      validar y limpiar el buffer con `while (getchar() != '\n')`;
      reutilízalo donde vuelvas a leer con `scanf`.
- [ ] Una condición de salida/derrota o victoria, aunque sea simple (por
      ejemplo, efectivo negativo, o un número de días objetivo).

### Fase 6 — Robustez y pruebas

- [ ] Compila y ejecuta con `-fsanitize=address,undefined` en un build de
      depuración aparte del de `make` normal.
- [ ] Pasa `valgrind` sobre un par de partidas completas jugadas a mano.
      Cero "definitely lost" antes de dar el proyecto por estable.
- [ ] Repasa cada función pública preguntándote: "¿qué pasa si me pasan
      `NULL` o un `Id` fuera de rango aquí?" — el patrón ya está en casi
      todo el código existente, solo falta que compruebes que ninguna
      función nueva rompe esa costumbre.

### Fase 7 — Extensiones (opcional, cuando lo de arriba esté sólido)

Ideas para cuando el núcleo funcione y quieras seguir practicando, sin
orden concreto: guardado/carga de partida en fichero, eventos aleatorios
(huelgas, subida de combustible), asignación de aviones a franjas horarias,
IA simple de una aerolínea rival, estadísticas al final de la partida.

## 5. Caja de herramientas

Compilación de depuración con sanitizers (no toca tu `Makefile`, es un
comando aparte):

```sh
gcc -Wall -Wextra -std=c99 -IIncludes -g -fsanitize=address,undefined \
    main.c Src/*.c -lm -o airplane_debug
```

Valgrind sobre el binario normal:

```sh
make clean && make
valgrind --leak-check=full --show-leak-kinds=all ./airplane
```

Git — recordatorio de tu propio flujo, ya usado en el historial:

```sh
git status
git add <ficheros concretos>       # evita `git add -A` a ciegas
git commit                         # mensajes cortos, en el estilo que ya usas
```

## 6. Cómo pedirme ayuda a partir de ahora

Para que esto siga siendo tu aprendizaje y no mi código:

- Pide **revisión**, no implementación: "¿ves algún problema de memoria en
  esta función?" en vez de "escríbeme esta función".
- Pide que te haga **preguntas** sobre una parte que no te cuadre, en vez
  de la solución directa.
- Si te atascas de verdad, pide una **pista mínima** primero ("dame una
  pista, no la respuesta") y solo escala si con eso no basta.
- Cuando termines una fase, pide una revisión de diseño antes de dar por
  cerrado el módulo — es mucho más barato corregir un diseño que una
  implementación ya extendida por todo el proyecto.
