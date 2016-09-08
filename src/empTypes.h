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

/*Struct used in the parsing argument

Estructura utilizada para el manejo de los archivos dentro del parseo*/

typedef struct{
	char **list;   //Lista de archivos / List of files
	char *in;      //Nombre de archivo de entrada / Name of input
	char *out;     //Nombre de archivo de salida / Name of output
	size_t compress;//Indica si se debe tratar con formato gz / It indicates whether to deal with format gz 
	size_t silent; //Indica si se debe ejecutar el programa en modo silent / It indicates if the program is execute in silent mode 
	size_t cant;   //Cantidad de archivos / Quantity of files
	size_t list_size;  //Tamaño total del arreglo / Full size of the array
	size_t size;   //Tamaño seteado para los Strings In y Out / Size of the strings In and Out
	size_t num_in; //Puede tomar valores 0 y 1 				/ Can be 0 or 1
	size_t num_out;//0=predeterminado, 1=nombre ingresado	/0 = default, 1 = input path 
}files_array;

/*Principal structure used in the parsing argument

Estructura principal utilizada para el parseo de argumentos*/

typedef struct{
	char option[2]; //Arreglo de char con la opcion elegida / Array of char with the option chosen
	size_t op_index;//Index de la opcion / Index de la opcion
	files_array operands;
	int num_op;  //Siempre que tenga un valor diferente de 1 es error / If the value is diferent to 1 is error
}option_args;

#endif
