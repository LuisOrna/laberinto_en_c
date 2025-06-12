La idea del programa es generar laberintos aleatorios, con tamaño elegido por el usuario. Actualmente el código tiene definidas max_filas = 40 y max_columnas = 40. Por ende, un laberinto de mayor tamaño no será posible a menos que se modifiquen estos valores. Modificar estos valores a un número muy alto sin utilizarlo realmente sería un desperdicio de memoria.
La cantidad de filas y columnas debe ser impar, por ende si el usuario ingresa un tamaño par, existe una validación que lo convierte en impar sumándole 1.

Instrucciones de compilación y ejecución
bashgcc dia4.c -o laberinto
./laberinto



Formato de entrada y salida
El programa utiliza los siguientes símbolos para representar el laberinto:
# = Pared
(espacio) = Camino libre
e = Entrada del laberinto
s = Salida del laberinto
* = Camino de la solución marcado por el algoritmo

Cómo se genera el laberinto
El laberinto se genera con un algoritmo DFS (Depth-First Search), específicamente Recursive Backtracker que explora en profundidad todos los espacios posibles, por lo cual está garantizado que la entrada y la salida están conectadas por al menos un camino. El algoritmo siempre inicia rompiendo y abriendo espacios en coordenadas impares (filas, columnas) y posteriormente rompe la pared vecina (coordenadas pares). Por este motivo, en caso de que las filas/columnas sean pares, quedaría una doble pared no perforada.
El algoritmo DFS que genera el laberinto de manera aleatoria está implementado en un bucle while. La aleatoriedad está iniciada por la función srand() que proporciona una semilla diferente basada en el tiempo para cada ejecución de la función rand(), que es la que elige caminos aleatorios.


Algoritmo para resolver el laberinto
El algoritmo se resuelve también con DFS usando Recursive Backtracking que explora todas las posibilidades posibles y no se detiene hasta encontrar que ninguna posibilidad llega a 's' (return 0) o que alguna posibilidad llega a 's' (return 1).
El algoritmo está concentrado al 100% en una función recursiva.


Medición de tiempos y mejoras identificadas
Al medir los tiempos me di cuenta de que para tamaños grandes (filas y columnas > 30) era muy lenta la ejecución del primer backtracker para generar el laberinto. Esto se puede solventar fácilmente quitando las funciones de imprimir el laberinto en cada iteración. Al quitar estas impresiones, las ejecuciones de ambos algoritmos son casi inmediatas.


Limitaciones conocidas
Tamaño máximo: El laberinto está limitado a 40x40 debido a la definición estática de la matriz
Validación de entrada: El programa no valida entradas negativas o cero del usuario
Memoria fija: Se reserva memoria para el tamaño máximo independientemente del tamaño real solicitado
Dimensiones impares obligatorias: Solo funciona correctamente con dimensiones impares (se ajusta automáticamente)

El próximo punto de mejora de este proyecto es hacer que el tamaño de la estructura pueda ser definido de manera dinámica. Esto permitirá quitar limitaciones de tamaño. También, en caso de aplicar esa mejora, será necesario comenzar a tomar en cuenta aspectos de manejo y liberación de memoria que con la configuración actual no están contemplados.
