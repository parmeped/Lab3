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

