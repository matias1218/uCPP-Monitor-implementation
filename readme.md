# Manual de Usuario

Este manual explica de manera breve los requerimientos y el uso del programa.

####  Compilación
Para compilar el programa, basta con abrir una terminal sea en Linux o Windows dentro de la carpeta donde se encuentra el archivo de programa y ejecutar el comando:

###### Linux:

	$ make    
 
#### Ejecución
Para ejecutar el programa, basta con ejecutar por consola el siguiente comando:

	 $ ./pipeline -c X -u Y -n Z -b 

Parametro  | Valor
------------- | -------------
X  | Cantidad de imagenes
Y  | Umbral en valor pixel
Z  | Umbral porcentaje de negro

El valor -b puede ser omitido si no se requiere la visualización de resultados por pantalla.

### Consideraciones Generales
El programa procesará imagenes solo si estas poseen el nombre:
> image_N.bmp 

donde  N especifica el valor numérico de la imagen (1..n).
La secuencialidad de la lectura de multiples imagenes dependerá de que se siga este orden para cada imagen.

Ejemplo:
> image_1.bmp
image_2.bmp
image_3.bmp
.
.
.
image_N.bmp