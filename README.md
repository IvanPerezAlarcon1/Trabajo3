# PuntajesPSU_SQL
<<<<<<< Updated upstream
 
=======
## Descripcion
Este repositorio contiene un programa en C++ (llenarPuntajesSQL) para llenar una base de datos PostgreSQL con registros de la forma rut asociado de 6 numeros aleatorios correspondientes a puntajes PSU.Genera un rango aproximado de 5 millones de lineas de texto.

Se realiza el procesamiento de este archivo para obtener un nuevo archivo `.csv` que contenga por cada linea el rut y el promedio de los 6 puntajes asociados a dicho rut.
Este procedimiento se implementa realizando el procesamiento de datos en el servidor SQL para luego imprimir los resultados obtenidos en un carchivo `.csv` de forma que cada linea contengael rut y su promedio asociado separado por `;`.
## Compilacion
```
make -C llenarPuntajesSQL
```
## Ejecucion
```
time ./llenarPuntajesSQL/dist/programa
```
## Integrantes
- Léster Vasquez
- Ivan Pérez
- Sebastian Pérez
>>>>>>> Stashed changes
