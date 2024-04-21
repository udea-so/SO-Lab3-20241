# SO-Lab3-20201: Paralelización de la función SAXPY.

# Objetivos
Paralelizar el código presentado haciendo uso de hilos con la librería pthreads.

# SAXPY
La función SAXPY (single-precision A\*X plus Y) es una función básica en el álgebra lineal. Esta función es usada recurrentemente para el desarrollo de métodos numéricos, en el procesamiento de señales, etc.

La función saxpy desarrolla la multiplicación de un valor escalar *a* por un vector **X**, luego el resultado se suma a un vector **Y**, el resultado usualmente es almacenado nuevamente en el vector **Y**, de esta manera la formulación es la siguiente:

**Y** = a \* **X** + **Y** 

Aunque la función saxpy no es particularmente difícil a nivel computacional, cuando se tiene una gran cantidad de datos a procesar puede ser ser usada como ejemplo para explorar la programnación paralela.  

En el ejemplo presentado en este laboratorio, vamos a implementar una función saxpy iterativa, con el fin de obtener un tiempo de ejcución adecuado para el desarrollo de este ejercicio:

```
para un número máximo de iteraciones max_iters haga: 
    Y = a * X + Y 
fin
```
Con el fin de hacer el ejercicio más divertido, el programa base propuesto, también calcula los valores promedio de cada iteración de Y. 


# Pasos sugeridos para el desarrollo del laboratorio
1. Clone este repositorio, compile y ejecute el código, trate de entenderlo, no es difícil.
2. Defina una estrategia para el desarrollo de la versión paralela: ¿Cuál es la mejor forma de dividir el trabajo entre los hilos disponibles?
3. Desarrolle una primera versión paralela dividiendo el trabajo entre solo 2 hilos, verifique que el código siguee funcionando correctamente (comparando el resultado con una cversión secuencial) y luego verifique que el tiempo de ejecución disminuye en la versión paralela.
4. Implemente un versión paralela que distribuya el trabajo de manera automática para un número n de hilos. Se realizarán pruebas para n = 1, 2, 4, y 8 hilos.
5. Desarrolle un informe donde evalue el desempeño su versión paralela, tomando el tiempo de ejecución del programa utilizando varios hilos, y desarrollando varias repeticiones (mínimo 10 por caso), grafique los resultados y analice las gráficas.

Fecha de entrega: Jueves 10 de Diciembre de 2020
