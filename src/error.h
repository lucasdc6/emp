#ifndef ERROR_H
#define ERROR_H

#define OPEN 1 //Retorna 1 si hubo un error con la apertura de un archivo
#define READ 2 //Retorna 2 si hubo un error con la Lectura de archivos
#define WRITE 3 //Retorna 3 si hubo un error con la Escritura de archivos
#define CREATE 4 //Retorna 4 si hubo un error con la creacion de archivos
#define CUR 5 //Retorna 5 si hubo un error con el posicionamiento del cursor en el archivo
#define NUM_FILES 6 //Retorna 6 si hubo un error con el numero de archivos ingresado
#define NO_FILES 7 //Retorna 7 si no se pudo encontrar los archivos buscados
#define OP_IN 8 //Retorna 8 si hubo un error con los archivos de entrada
#define OP_OUT 9 //Retorna 9 si hubo un error con los archivos de salida
#define NO_OPERATIONS 10 //Retorna 10 si hubo un error con la cantidad de opciones ingresadas
#define FILE_UNPACK 11 //Retorna 11 si hubo un error con el nombre ingresado del archivo a desempaquetar
#define OP_LIS_INC 12 //Retorna 12 si es una opcion incorrecta
#define OPEN_DIR 13 //Retorna 13 si hubo un error al abrir un directorio
#define FORMAT 14 //Retorna 14 si el formato del archivo de entrada es incorrecto
#define W_NAME 15 //Retorna 15 si hubo problemas con el nombre del archivo de salida

/*
   "errors_2p" - Funcion de manejo de errores con 2 parametros de salida en el mensaje
   (el primer paramero es el path definido más adelante, el segundo es un string
   proveniente del strerror utilizando el errno)

Recibe:
-Un archivo para cerrar(se especifica con 0 o 1, en el anteultimo parametro
que se debe hacer), de ser 1 se recibe NULL.
-Una estructura de argumentos para liberar su memoria(se especifica con 0 o 1,
en el ultimo parametro, que se debe hacer), de ser 1 se recibe NULL.
-Un mensaje el cual imprimir en la salida de error estandar
-Un path para especificar el archivo el cual esta involucrado en el error
-Una constante con el numero de salida(Las constantes pueden ser las definidas
al inicio de este documento), utilizada en la operacion "exit".
-Un booleano(size_t) que especifica si se debe o no cerrar el archivo, 0 se
debe cerrar, 1 no se debe cerrar(no hay archivo para cerrar).
-Un booleano(size_t) que especifica si se debe o no liberar el espacio
utilizado en la estructura, 0 se debe liberar, 1 no se debe liberar
(no hay estructura)*/
void errors_2p(FILE*, option_args*, const char*, const char*, const int, size_t, size_t);

/*
   "errors_2p" - Funcion de manejo de errores con 1 parametro de salida(impreso con el strerror
   utilizando el errno) en el mensaje.

Recibe:
-Un archivo para cerrar(se especifica con 0 o 1, en el anteultimo parametro
que se debe hacer), de ser 1 se recibe NULL.
-Una estructura de argumentos para liberar su memoria(se especifica con 0 o 1,
en el ultimo parametro, que se debe hacer), de ser 1 se recibe NULL.
-Un mensaje el cual imprimir en la salida de error estandar.
-Una constante con el numero de salida(Las constantes pueden ser las definidas
al inicio de este documento), utilizada en la operacion "exit".
-Un booleano(size_t) que especifica si se debe o no cerrar el archivo, 0 se
debe cerrar, 1 no se debe cerrar(no hay archivo para cerrar).
-Un booleano(size_t) que especifica si se debe o no liberar el espacio
utilizado en la estructura, 0 se debe liberar, 1 no se debe liberar
(no hay estructura)*/
void errors_1p(FILE*, option_args*, const char*, const int, size_t, size_t);

/*
   "errors_msg" - Funcion de manejo de errores que solo imprime un mensaje de error.

Recibe:
-Un archivo para cerrar(se especifica con 0 o 1, en el anteultimo parametro
que se debe hacer), de ser 1 se recibe NULL.
-Una estructura de argumentos para liberar su memoria(se especifica con 0 o 1,
en el ultimo parametro, que se debe hacer), de ser 1 se recibe NULL.
-Un mensaje el cual imprimir en la salida de error estandar.
-Una constante con el numero de salida(Las constantes pueden ser las definidas
al inicio de este documento), utilizada en la operacion "exit".
-Un booleano(size_t) que especifica si se debe o no cerrar el archivo, 0 se
debe cerrar, 1 no se debe cerrar(no hay archivo para cerrar).
-Un booleano(size_t) que especifica si se debe o no liberar el espacio
utilizado en la estructura, 0 se debe liberar, 1 no se debe liberar
(no hay estructura)*/
void errors_msg(FILE*, option_args*, const char*, const int, size_t, size_t);

#endif
