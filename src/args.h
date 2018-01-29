#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>
#include "empTypes.h"

/*Macros utilizadas en el programa principal para enlazar los indices de las
  operaciones contenidos en la estructura del parseo de argumentos con las
  operaciones contenidas en la estructura enum definida debajo de estas macros*/
#define OP_PACK 0
#define OP_UNPACK 1
#define OP_REPACK 2
#define OP_UNPACKALL 3
#define OP_DETAIL 4
#define OP_LIST 5

/*Utilizado en el parseo de argumentos y en el main del programa, enlazado
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

/*Función que libera completamente el espacio alocado para la estructura
  files_array*/
void free_files_array(files_array *);

/*Función principal para el parseo de argumentos*/
option_args *parse(int, char**);

#endif
