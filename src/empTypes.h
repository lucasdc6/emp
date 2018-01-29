/* Copyright (C) 2016 Lucas Di Cunzolo

   This file is part of EMP.

   EMP is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   EMP is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with EMP. If not, see <http://www.gnu.org/licenses/>.     */

#ifndef EMPTYPES_H
#define EMPTYPES_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

#define MAX_PATH 1024 //maximo de caracteres admitidos en los path

/*Estructura del registro principal del paquete*/

typedef struct{
  char magic[3];
  unsigned char version;
  uint32_t entries;
  uint64_t reserv1;
  uint64_t reserv2;
}t_head;

/*Estructura del registro principal de cada archivo contenido en el paquete*/

typedef struct{
  uint64_t tam;
  time_t date;
  uint64_t reserv1;
  uint64_t reserv2;
  char *path;
}t_head_file;

/*Estructura utilizada para el manejo de los archivos dentro del parseo*/

typedef struct{
  char **list;   //Lista de archivos
  char *in;      //Nombre de archivo de entrada
  char *out;     //Nombre de archivo de salida
  size_t cant;   //Cantidad de archivos
  size_t list_size;  //Tamaño total del arreglo
  size_t size;   //Tamaño seteado para los Strings In y Out
  size_t num_in; //Puede tomar valores 0 y 1
  size_t num_out;//0=predeterminado, 1=nombre ingresado
}files_array;

/*Estructura principal utilizada para el parseo de argumentos*/

typedef struct{
  char option[2]; //Arreglo de char con la opcion elegida
  size_t op_index;//Index de la opcion
  files_array operands;
  int num_op;  //Siempre que tenga un valor diferente de 1 es error
}option_args;

#endif
