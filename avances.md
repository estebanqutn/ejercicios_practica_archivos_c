## Avances – Archivos binarios en C

Se implementaron las funciones `cargarPersonas()` y `guardarPersonas()` para leer y escribir registros de personas en archivos binarios (`.dat`), utilizando `fopen()`, `fread()`, `fwrite()` y `fclose()`. Se incorporaron controles para validar la cantidad de registros, verificar la correcta lectura y escritura, detectar archivos inexistentes y controlar errores de cierre.

Durante el desarrollo se trabajó en la depuración del programa mediante mensajes de seguimiento, identificando errores en la lectura de datos y comprendiendo el funcionamiento de la evaluación de cortocircuito del operador `&&`. También se mejoró el control de errores mediante variables booleanas y valores de retorno.

Finalmente, se reorganizó el flujo del `main()` para respetar el orden lógico del programa: primero cargar los datos, luego trabajar con ellos y, por último, guardar los cambios realizados.