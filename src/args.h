#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>
#include "empTypes.h"

/*Macros used in the principal program to link the operations index content
in the structure of the parsing arguments with the operations contents in the
structure enum declared

Macros utilizadas en el programa principal para enlazar los indices de las
operaciones contenidos en la estructura del parseo de argumentos con las
operaciones contenidas en la estructura enum definida debajo de estas macros*/
#define OP_PACK 0
#define OP_UNPACK 1
#define OP_REPACK 2
#define OP_UNPACKALL 3
#define OP_DETAIL 4
#define OP_LIST 5

/*Used in the parsing arguments and in the main program, linked directly with the
basic operations

Utilizado en el parseo de argumentos y en el main del programa, enlazado
directamente con las operaciones basicas del empaquetador*/

enum {
  PACK,
  UNPACK,
  REPACK,
  UNPACKALL,
  DETAIL,
  LIST,
  OPTLEN
};

/*Function that releases the space allocated by the structure files_array

Función que libera completamente el espacio alocado para la estructura
files_array*/
void free_files_array(files_array *);

/*Principal function of parsing arguments

Función principal para el parseo de argumentos*/
option_args *parse(int, char**);

#endif
