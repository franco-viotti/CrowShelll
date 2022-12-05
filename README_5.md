Laboratorio N5
# MyShell advance
### SOI - FCEFyN - UNC - 2022


## Objetivo
Basandonos en lo realizado en el Laboratorio 4, se busca:

- Utilizar mecanismos de concurrencia e IPC.
- Ampliar las características de un intérprete de línea de comandos al estilo Bourne shell.
- Comprender el uso de la API de señales del SO


## Duración
Con el material dado en clase, este laboratorio está diseñado para resolverse entre 8 y 10 horas.


## Introducción
Este trabajo práctico consta en la elaboración de un programa en lenguaje C sobre _GNU/Linux_. El trabajo se divide en soluciones incrementales.

## Actividades
#### 1. Signal Handling
Si se ingresa alguna de las combinaciones CTRL-C, CTRL-Z o CTRL-/\, las señales resultantes (**SIGINT**, **SIGTSTP**, **SIGQUIT** respectivamente) deben ser enviadas al trabajo (job) en ejecución de primer plano en vez de a _myshell_. Si no hay un trabajo (job) en ejecución de primer plano, no debe suceder nada.

#### 2. Pipe
_myshell_ provee la funcionalidad de un pipe a través del operador **|** (pipe). El mismo conecta la salida estándar del proceso (stdout) lazando por el comando de la izquierda del pipe con la entrada estándar del proceso (stdin) que se genera con el comando a la derecha del pipe.

Ejemplos:
```
$ last <username> | wc -l
$ ps aux | grep firefox
$ grep bash /etc/passwd | cut -d “:” -f 1 | sort -r
```
##### Responder:
¿Dónde se encuentran los pipes en el filesystem, qué atributos tienen?


#### 3. I/O redirection 
Se debe soportar redirección de entrada/salida en _stdin_ y/o _stdout_. 

Por ejemplo:
```
program arg1 ar2 < inputfile > outputfile
```

Ejecuta la el programa _program_ con los arguments _arg1_, _arg2_. _stdin_ es reemplazado por _inputfile_ y _stdout_ por _outputfile_.
La redirección debe funcionar para el comando interno _echo_.


## Criterio de desarrollo
Dado que este laboratorio propone agregar funcionalidades a un proyecto existente, deben utilizar correctamente el workflow de desarrllo. Es decir:
- Se debe realizar un fork al proyecto original (laboratorio 4)
- Se implementan las nuevas funcionalidades
- Se realiza un Pull Request en un nuevo branch en el repositorio del laboratorio 4.


## Criterios de Corrección
- Se debe compilar el código con los flags de compilación: -Wall -Pedantic -Werror 
- Dividir el código en módulos de manera juiciosa.
- Estilo de código.
- El código no debe contener errores, ni warnings.
- El código no debe contener errores de cppcheck.
- _myshell_ no debe crear procesos zombies.

## Qué se debe Entregar
- Informe del desarrollo del proyecto (markdown).
- Código (funcionando bajo las especificaciones dadas y bajo cualquier caso de test de parámetros de entrada).
- Makefile
- Todo en el GitHub


### Links
- [1] https://www.toptal.com/git/git-workflows-for-pros-a-good-git-guide
- [2] https://www.dataschool.io/how-to-contribute-on-github/
