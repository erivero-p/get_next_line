# get_next_line
Una función que toma un file descriptor y devuelve una línea leída del archivo en cuestión.

Llamar varias veces a la función devolverá las siguientes líneas.

# Project Tree

```bash
.
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
└── main.c
```

# Consideraciones previas

### ***Sobre la flag -D***

Es una flag que permite asignar un valor a una variable al compilar. Como la función debe compilar también sin la flag -D, en el header hay que darle un valor. 

### *Sobre las variables estáticas*

Una variable estática es aquella que ha sido ubicada estáticamente y cuyo tiempo de vida se extiende durante toda la ejecución del programa. Suele tener un ámbito más amplio que otras variables. Se pueden establecer una vez durante el tiempo de ejecución, o cambiar en múltiples ocasiones durante la ejecución del programa. 

Es decir, las variables estáticas conservan su valor pese a que salgamos de la función: si estamos en un bucle llamando a una función y esa función tiene una variable estática en la que aplicamos cambios, estos se conservan. 

Se declararán añadiendo static: 

`static char *str;`

### *Sobre read: #include <unistd.h>*

`int read (int fd, void *buffer, unsigned bytes);`

Read recibe un file descriptor, un puntero a un área de memoria, y un número de bytes a transferir al buffer. Devuelve el número de bytes que se han leído realmente o -1 en caso de que haya habido error de llamada. En el puntero al área de memoria recibe como argumento, acumulará los bytes leídos. En su memoria interna, almacena la última posición leída de fd. 

En este caso, el número de bytes a leer, será BUFFER_SIZE, y en cada llamada a read no se pueden leer ni más, ni menos bytes. 

# Project Structure

Nuestra función debe cumplir varios pasos fundamentales:

- Llamar a `read` reiteradamente hasta que encuentre un caracter newline `\n`
- Tomar una línea, ignorando lo que `read` haya almacenado tras el `\n`
- Liberar la línea printeada y almacenar lo leído tras el `\n` para posteriores llamadas

# get_next_line

En base a lo anterior, la función deberá declarar la variable estática en la que ir acumulando lo leído, y llamar a funciones que realicen las tres tareas anteriores. En mi caso: 

- `ft_get_piece`
- `ft_get_line`
- `ft_acumclean`

### `ft_get_piece`

La función recibe el acumulado que haya en la variabale estática y el fd. Va alojando en una string temporal `tmp` cada lectura de `BUFFER_SIZE` caracteres que haga read. Irá uniendo cada lectura a la anterior y, a la vez, buscando si dentro de lo leído hay un `\n`, en cuyo caso, romperá el bucle y devolverá lo acumulado.

### `ft_get_line`

Esta función recibe la string acumulada hasta ahora y, alojando memoria para la misma, copia hasta el salto de línea e ignora todo lo que haya tras el mismo. En caso de que no nos encontremos al final del documento, añadirá un salto de línea después.

### `ft_acumclean`

Ya tenemos la línea limpia que será el valor de retorno de nuestra función `get_next_line`, sin embargo, la función deberá trabajar correctamente en caso de posteriores llamadas a la misma. 

Para ello, es necesario una función que, de nuestra variable estática acumulada hasta ahora, libere la línea ya guardada, y devuelva sólo lo que se encuentre tras el salto de línea, para usarlo en posteriores llamadas a la función.
