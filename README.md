# SO-Lab3-20241: Paralelización de la función SAXPY.

## Objetivos

> Paralelizar el código presentado haciendo uso de hilos con la librería pthreads.

## SAXPY

La función SAXPY (single-precision A\*X plus Y) es una función básica en el álgebra lineal. Esta función es usada recurrentemente para el desarrollo de métodos numéricos, en el procesamiento de señales, etc.

La función saxpy ([simulación](https://pythontutor.com/render.html#code=%23include%20%3Cstdio.h%3E%0A%0Aint%20main%28%29%20%7B%20%0A%20%20int%20N%20%3D%206%3B%0A%20%20float%20a%3D3.1415%3B%0A%20%20float%20x%5B%5D%3D%7B1,2,3,4,5,6%7D%3B%0A%20%20float%20y%5B%5D%3D%7B7,8,9,0,1,2%7D%3B%0A%20%20for%28int%20i%3D0%3B%20i%3CN%3B%20i%2B%2B%29%7B%0A%20%20%20%20y%5Bi%5D%3Da*x%5Bi%5D%2By%5Bi%5D%3B%0A%20%20%7D%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false)) desarrolla la multiplicación de un valor escalar $a$ por un vector $\mathbf{\vec{X}}$, luego el resultado se suma a un vector $\mathbf{\vec{Y}}$, el resultado usualmente es almacenado nuevamente en el vector $\mathbf{\vec{Y}}$, de esta manera la formulación es la siguiente:

> $$ \mathbf{\vec{Y}} = a*\mathbf{\vec{X}} + \mathbf{\vec{Y}} $$


Aunque la función saxpy no es particularmente difícil a nivel computacional, cuando se tiene una gran cantidad de datos a procesar puede ser ser usada como ejemplo para explorar la programación paralela.  

En el ejemplo presentado en este laboratorio ([saxpy.c](src/saxpy.c)), vamos a implementar una función saxpy iterativa, con el fin de obtener un tiempo de ejcución adecuado para el desarrollo de este ejercicio:

```
para un número máximo de iteraciones max_iters haga: 
    Y = a * X + Y 
fin
```

Con el fin de hacer el ejercicio más divertido, el programa base propuesto, también calcula los valores promedio de cada iteración de Y. 

## Compilación y ejecución

### Modo DEBUG

```
make clean
make DEBUG=1
./saxpy
```

### Modo RELEASE

```
make clean
make DEBUG=0
./saxpy
```

## Pasos sugeridos para el desarrollo del laboratorio

1. Haga un fork de este repositorio. Luego, trabajando sobre este, compile y ejecute el código, trate de entenderlo, no es difícil.
2. Defina una estrategia para el desarrollo de la versión paralela: ¿Cuál es la mejor forma de dividir el trabajo entre los hilos disponibles?
3. Desarrolle una primera versión paralela dividiendo el trabajo entre solo 2 hilos, verifique que el código sigue funcionando correctamente (comparando el resultado con una versión secuencial) y luego verifique que el tiempo de ejecución disminuye en la versión paralela.
4. Implemente un versión paralela que distribuya el trabajo de manera automática para un número *n* de hilos. Se realizarán pruebas para n = 1, 2, 4, y 8 hilos.
5. Desarrolle un informe dónde evalúe el desempeño su versión paralela, tomando el tiempo de ejecución del programa utilizando varios hilos, y desarrollando varias repeticiones (mínimo 10 por caso). Grafique los resultados y analice las gráficas.

## Recursos adicionales

A continuación, se detallan algunos enlaces con material del texto guia que puede ser de utilidad para el desarrollo de la practica:
1. **Laboratory: Tutorial** [[doc]](https://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf)
2. **Interlude: Thread API** [[doc]](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-api.pdf) | [[code]](examples_ostep/threads-api/)