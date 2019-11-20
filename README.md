# TP2_SO1
Trabajo practico numero 2 de la materia Sistemas Operativos 1.\
\
*Autores:* Agustinoy Jeremias y Viccini Patricio 

## Descripcion:
>Consiste en una programa escrito en C para GNU/Linux que busca imitar a una *linux shell* 

---
## **Para el usuario:**

Este programa puede recibir un tipo de argumento, el mismo debe ser un **batch-file** que contenga comandos a ser ejecutados por la shell. Si no recibe comandos imprime un *prompt* y espera recibir comandos por teclado.\
Esta shell soporta tanto algunos comandos internos como tambien la ejecucion de programas externos.

### Prompt :
>Contiene el user y la ruta al directorio actual, se 
imprime cada vez que se espera por la entrada de un comando y se actualiza segun se realicen cambios de directorio.

### Comandos internos :
>**cd *[directorio]*** 
> 
>Cambia el directorio actual a *[directorio]*, si este no existe muestra un mensaje de error indicando el motivo del error.
>
>**clr**
>
>Limpia la pantalla de la shell
>
>**echo *[comentario]***
>
>Muestra *[comentario]* en la pantalla seguido por una línea nueva.
>
>**quit**
>
>Cierra el programa, es decir nuestra shell.

### Invocacion de programas :
> Entradas del usuario que no sean comandos internos son interpretados como la invocación de un programa, ejecutandose el mismo como un hijo de la shell.

### Ejecucion en segundo plano :
>Si se ingresa un ampersand "**&**" al final de la línea de comando, la shell retornara al prompt inmediatamente luego de lanzar al programa a ejecutarse, dejando al mismo ejecutandose en 2do plano.

### Redireccion de E/S :
> Soporta las redirecciones de entrada y de salida, marcadas por los operadores "**<**" y "**>**" respectivamente.\
>Esta redireccion funciona tanto para programas invocados como para el comando interno *echo*

### Batch-file:
> myshell es capaz de tomar sus comandos a ejecutar desde un archivo. Por ejemplo,
si la shell es invocada con un argumento ​*myshell **batchfile​***.\
>Este contiene un
conjunto de comandos de línea para que la shell ejecute.
Cuando se alcanza el fin de archivo (EOF), myshell se cierra.

---
## **Para el desarrollador:**

### Funciones a destacar:
Aqui se plantean funciones de la biblioteca *unistd.h* las cuales nos parecen de principal relevancia.

> * chdir(*directory*) : realiza el cambio de directorio y modifica la variable de entorno **PWD**.
> * fork() : Clona al proceso que lo llama, creando una copia exacta. En nuestro programas lo utilizamos para crear un proceso sobre el cual ejecutar el comando que no entra dentro de los comandos internos.
> * execvp(*file, argvs*) : ejecuta el *file* buscandolo en la variable de entorno "**PATH**" y al mismo lo ejecuta con los argumentos *argvs*. Esto se utiliza en el proyecto para ejecutar los programas dentro de los procesos hijos de la shell. 
> * waitpid(*pid, status_loc, options*) : Espera a que el proceso hijo con ese *pid* finalice. Lo utilizamos en el proyecto cuando se ejecuta un programa cuyo comando no finaliza con "**&**".
> * dup(*fd*) : duplica el *fd*, devolviendo el nuevo  **file descriptor** sobre el mismo archivo.
> * dup2(*fd, fd2*) : duplica el *fd* al *fd2* haciendo que este ultimo pase a "apuntar" al mismo archivo que *fd*. Tanto dup() como dup2() son utilizados en el proceso de redireccionamiento de entrada salida para el manejo de los file descriptors.

### El proceso de desarrolo de este sofware fue el siguiente:
>Se comenzo **probando la shell de linux** para compender como debia de verse la ejecucion de nuestro programa.\
>Luego el desarrollo fue **incremental** de la forma en que lo recomienda la consigna del TP, siguiendo los requrimientos que debia cumplir.\
>Al principio trabajamos enteramente sobre un unico archivo *.c* hasta que se optuvo el comportamiento deseado del programa.\
>Luego se crearon *archivos separados segun nuestro juicio* para dividir el codigo en modulos mas simples.\
>Por ultimo se produjo un archivo **makefile** para manejar la creacion del ejecutable y las dependecias entre archivos.



