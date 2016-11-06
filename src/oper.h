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

#ifndef OPER_H
#define OPER_H

/*Macros used by the function list
Macros utilizadas por la función list*/
#define NAME 0
#define DATE 1
#define SIZE 2

/*Used by the ok_input function to determine if is a .gz file

Usado por la funcion ok_input para determinar si es un archivo .gz*/
#define IS_GZ(dir) dir[strlen(dir)-3] != '.' && dir[strlen(dir)-2] != 'g' && dir[strlen(dir)-1] != 'z'

/*Here are declared the diferents headers used by the basic functions

Se encuentran definidos los distintos headers de las distintas funciones
enlazadas a las operaciones basicas del programa*/

/*Package in the file of output(first parameter) a single file(path at the second
parameter), used by big_pack, pack_dir and repack

Empaqueta en el archivo de salida(primer parametro) un solo archivo(path
especificado como segundo parametro), usado por big_pack, pack_dir y repack*/
int small_pack(FILE*, char*);

/*Package in the file of output(first parameter) the files content in a directory
(path at the second parameter), used by big_pack and repack

Empaqueta en el archivo de salida(primer parametro) los archivos contenidos en un
directorio(path especificado como segundo parametro), usado por big_pack y repack*/
int pack_dir(FILE*, const char*);

/*Compress the source file in the destination file(first and second parameter respectively)
in the compress level specified(third parameter)

Comprime el archivo fuente en el destino (primer y segundo parametro respectivamente)
en el nivel de compresion especificado(tercer parametro)*/
int compress_files(FILE*, FILE*, int);

/*Package in the file of output(first parameter) the files specified, content in the
structure(second parameter)
The file is created from the beginning

Empaqueta en un archivo de salida(primer parametro) los archivos especificados,
contenidos en la estructura(segundo parametro).
El archivo se crea de cero*/
int big_pack(FILE*, option_args*);


/*Package in the file of output(first parameter) the files specified, content in the
structure(second parameter)
An existing file is opened for editing

Empaqueta en un archivo de salida(primer parametro) los archivos especificados,
contenidos en la estructura(segundo parametro).
Se abre un archivo ya creado para modificarlo*/
int repack(FILE*, option_args*);

/*Descompress the source file in the destination file(first and second parameter respectively)

Descomprime el archivo fuente en el archivo destino(primer y segundo parametro respectivamente)*/
int descompress_files(FILE*, FILE*);

/*Unpacks the files from the input(first parameter) specified in the structure(second
parameter)

Desempaqueta los archivos del archivo de entrada(primer parametro) especificados en la
estructura(segundo parametro)*/
int unpack(FILE*, option_args*);

/*Unpacks all the files from the input(first parameter) specified in the structure(second
parameter)

Desempaqueta todos los archivos del archivo de entrada(primer parametro) especificados en la
estructura(segundo parametro)*/
int unpack_all(FILE*, option_args *args);

/*List by name, date of last modification and size(criterion specified in the
third parameter, using the macros stated above) all the files (conents in the first
parameter)

Lista por Nombre, Fecha de Ultima Modificacion y Peso(criterio especificado
en el tercer parametro, usando las macros declaradas arriba) todos los archivos
(contenidos en el primer parametro)*/
int list(FILE*, option_args *args, size_t);

/*Show the full details for a file received content in the structure(second parameter),
which is packaged in a file (first parameter)

Muestra los detalles completos de un archivo recibido contenido en la estructura
(segundo parametro), el cual se encuentra empaquetado(primer parametro)*/
int detail(FILE*, option_args *args);

/*Determines if is right the format of the file of input

Determina si el format del archivo de entrada es correcto*/
void ok_input(FILE*, const char*, int);

/*Determines if is right the name of the file of output

Determina si el nombre del archivo de salida es correcto*/
void ok_output(char*);

/*Determines if exist the file (second parameter) in the directory(first parameter) beafore
writing. If exist, asks if you want to change the name, if you want to rewrite or omit the
option (the program close).
The third parameter indicate if is a file or a packege. If is a packege, check if exist and
then check the name with the function ok_output. If is a file, only check if exist.

Determina si existe el archivo(segundo parametro) dentro del directorio(primer parametro)
antes de escribirlo, de existir pregunta si se quiere cambiar el nombre, si se quiere
sobrescribir o si no se debe hacer nada(se cerrara el programa).
El tercer parametro indica si es un paquete o un archivo, de ser un paquete
comprueba si existe y luego comprueba el nombre con la funcion ok_output, de ser de archivos
desempaquetados solo comprueba si existe*/
void file_exist(const char*, char*, size_t);

void new_path(char*);

/*Show the runtime.
The second parameter is used to not show the output if the program is executed in silent mode

Muestra el tiempo que tardo el programa en ejecutarse. El segundo parametro es utilizado
para no mostrar el tiempo transcurrido si el programa se ejecuta en modo silencioso*/
void print_time(clock_t, size_t);
#endif
