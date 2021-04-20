# Compilador
Un compilador es un tipo especial de traductor en el que el programa de origen o fuente es un lenguaje de alto nivel, 
y el código máquina o lenguaje objeto es de bajo nivel. (De c# a bin)

# Traductor 
Convierte el texto en un lenguaje, en texto en otro lenguaje.

# Interprete
Lee sentencia por sentencia, convierte en codigo objeto y ejecuta. La ejecucion de lenguaje compilado es mas rapida que vs interpretado porque
el compilador porque analiza todo el codigo fuente y luego lo convierte a codigo objeto, en vez de linea por linea.

# Gcc
Licenia GNU, portable, escrito en C.
Ej comando: 
    gcc -o {nombreDeseadoOutput} {archivoACompilar}

# Comandos linux basicos

ls -lh => Mostrar permisos
chmodugo+rwx [directorio] => Colocar permisos de lectura, escritura (w) y ejecución(x) al propietario (u), al grupo (g) y a otros (o) sobre el directorio.
chmodgo-rwx [directorio] => Quitar permisos.
chown [usuario] [fichero] => Change owner
ps [opciones] => Por defecto, muestra los procesos de su propia terminal. Con las opciones -ax muestra todos los procesos del usuario.
pstree => Arbol de procesos del sistema.
kill -9 [idProceso] => Kill process.
ipcs [opciones] => Recursos POSIX. -s : semaforos; -m: memoria compartida; -q : cola de mensajes.
ipcrm [opciones] => Elimina recurso indicado.

# Procesos
Codificacion => Compilacion => Ejecucion.
Cuando el programa se ejecuta se convierte en un proceso, se situa en la memoria principal y se ejecutan sus instrucciones. Finaliza cuando se cancela su ejecucion o se terminan sus instrucciones. 
Proceso: Tarea separada de otros procesos con sus propios permisos y responsabilidades. Utiliza los siguientes recursos compartidos: 
    - Tiempo de cpu
    - Memoria
    - Datos
    - Archivos y dispositivos de E/S
Se otorgan al momento de creacion o durante ejecucion.

##  Estados procesos
new => proceso creandose
running => proceso siendo ejecutado
waiting => proceso esperando (Por ej, un evento de algun dispositivo de E/S)
ready => esperando que se le asigne un procesador
terminated => finalizó su ejecucion y se le retiran los recursos utilizados

## Caracteristicas
Cada vez que se ejecuta un mismo programa, es un proceso diferente. El SO le asigna lo siguiente:
PID (Process id) => id del proceso
UID (User id), GID (Group Id) => usuario y grupo, determinan los permisos.
PPID (Parent process id) => eso

El contexto es su estado, definido por:
    - su codigo
    - valores de las variables de usuario globales y de sus estructuras de datos
    - valor de los registros de CPU
    - valores almacenados en su entrada de la tabla de procesos y en su area de usuario
    - contenido de sus stacks y kernel

## Comandos
Lista de procesos del sistema y caracteristicas.
PS [opciones] => 
    a: muestra los procesos creados por cualquier usuario y asociados a una terminal
    l: formato largo. Muestra prioridad, el PID del proceso padre
    u: formato de usuario. Incluye el usuario propietario del proceso y la hora de inicio
    U: usr: lista los procesos creados por el usuario “usr”
    x: muestra los procesos que no están asociados a ningún terminal del usuario (entre ellos, los “daemons”)

//****//
Jerarquia de procesos mediante estructura de arbol. Comienza por PID = 1. Si se especifica usuario, PSTREE de user.
PSTREE [opciones] [PID] [user] =>
    a: incluye en el árbol de procesos la línea de comandos que se usó para iniciar el proceso
    c: deshabilita la unión de procesos hijos con el mismo nombre (réplicas de un mismo proceso)
    G: usa los caracteres de línea para dibujar el árbol. La representación del árbol es más clara
    h: remarca la jerarquía del proceso actual
    n: por defecto,los procesos con mismo padre se ordenan por el nombre. Esta opción fuerza a ordenar los procesos por su PID
    p: incluye el PID de los procesos en el árbol

//****//
Lista de procesos estilo PS pero se actualiza constantemente.
TOP [opciones] => 
    i: ignora a los procesos inactivos listando únicamente los que utilizan recursos del sistema.
    d: especifica el ritmo de actualización de la pantalla en segundos. Es posible especificar decimales

Ordenes => 
    h: muestra una pantalla de ayuda.
    q: sale delaprogramación.
    k: kill, permite detener un proceso.
    r: permite alterar la prioridad de un proceso.

//****//
Similar a TOP, pero con mejor GUI.
HTOP [opciones] => 
    s: ordena por columna.
    u: muestra sólo los procesos de un usuario. 
    p: muestra sólo la información de los PIDs introducidos

//****//
Extra: 
    Ctrl + z: Pausa el proceso, se continua con fg. Se puede ver el estado y recursos compartidos mientras.

# Random
En c se utiliza la funcion Rand(), que devuelve entre 0 y RAND_MAX. para obtener entre 0 y N, se debe llamar:
rand() % (N + 1) => devuelve el módulo de la operacion y por ende un numero entre 0 y N. Para hacerlo entre M y N, se llama así:
rand() % (N - M + 1) + M

rand() calcula los numeros en base a un seed, y una vez compilado, devuelve siempre los mismos. Para evitar esto se llama a la funcion srand(), y 
se le suele pasar como seed el tiempo => srand(time(NULL)). Se la llama SOLO una vez al inicio de codigo.

# Parametro
Para pasar parametros por consola, se llama via => int main(argc, char *argv[]). el primero indica el nro total de parametros, el segundo son los parametros
en si. el primer parametro contiene el nombre del programa.

# Archivos
Antes de poder leer/modificar/escribir un archivo, es necesario abrirlo => 
FILE *archivo; 
archivo = fopen(char *nombre, char *modo)
Esto devuelve un puntero a una estructura que contiene informacion necesaria para manejar dicho archivo. Como todo, es necesario liberar recursos al finalizar
su utilizacion (fclose(archivo));

# Modo de apertura de archivo 
w: write; Si existe se elimina
r: read; Debe existir, sino error
a: append; Escritura al final, si no existe se crea vacio
w+: Lectura y escritura; Si existe se elimina
r+: Lectura y escritura; Si no existe se crea vacio
a+: Lectura y escritura al final; Si no existe se crea vacio

Si hay un error, fopen() devuelve NULL, por lo que siempre hay que validar archivo != NULL

# Operaciones sobre archivo
Leer valores con un determinado formato y guardarlos en variables:
    fscanf(archivo, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", &partida, &vuelo, destino);
Escribir valores con un determinado formato:
    fprintf(archivo, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", nro_partida, vuelos[rand_aux].vuelo, vuelos[rand_aux].destino);

Para saber si se ha llegado al final del archivo, existe la funcion:
    feof(archivo);
Esta devuelve 0 cuando llega al final, por lo que se puede negar !feof(archivo) para operar mientras no termine el archivo.

# Cadenas texto
Para trabajar con cadenas de texto, es necesario incluir "string.h". No existe el tipo dato string en C, por lo que se declara una cadena de char
de un largo determinado => char cadena[LARGO]. La longitud es de LARGO - 1 caracteres, ya que el ultimo se reserva para finalizar la cadena. 
NO SE PUEDE asignar caracteres a una cadena => cadena = "test". Es necesario utilizar los siguientes comandos:
- teclado:
    scanf("%s", cadena) 
- copiando:
    strcpy(cadena, "test")
- con sprintf: => no necesita "string.h"
    sprintf(cadena, "test")

para copiar desde una cadena hacia otra, se puede utilizar strcpy o sprintf con un tecer parametro:
    sprintf(cadena, "%s", cadena2)
sprintf puede ser usada tambien para copiar un decimal u otro tipo, a texto:
    sprintf(cadena, "%d", numero)
para copiar texto a numero, utilizar atoi(cadena)

- comparar:
    strcmp(cadena1, cadena2) => 0 iguales, 1 no.
- concatenar: 
    strcat(cadena1, cadena2)
ó:
    sprintf(cadena, "%s, %d", cadena1, numero)
- cantidad caracteres: 
    strlen(cadena)
ó 
    sizeof(cadena)

# Posix
Un sistema en tiempo real se define como uno que debe responder ante estimulos generados por el entorno dentro de un periodo de tiempo finito especificado.
Caracteristicas:

