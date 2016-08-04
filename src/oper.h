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

/*Macros utilizadas por la función list*/
#define NAME 0
#define DATE 1
#define SIZE 2

/*Se encuentran definidos los distintos headers de las distintas funciones
enlazadas a las operaciones basicas del programa*/

/*Empaqueta en el archivo de salida(primer parametro) un solo archivo(path
especificado como segundo parametro), usado por big_pack, pack_dir y repack*/
int small_pack(FILE*, char*);

/*Empaqueta en el archivo de salida(primer parametro) los archivos contenidos en un
directorio(path especificado como segundo parametro), usado por big_pack y repack*/
int pack_dir(FILE*, const char*);

/*Empaqueta en un archivo de salida(primer parametro) los archivos especificados,
contenidos en la estructura(segundo parametro).
El archivo se crea de cero*/
int big_pack(FILE*, option_args*);

/*Empaqueta en un archivo de salida(primer parametro) los archivos especificados,
contenidos en la estructura(segundo parametro).
Se abre un archivo ya creado*/
int repack(FILE*, option_args*);

/*Desempaqueta los archivos especificados */
int unpack(FILE*, option_args*);

/*Desempaqueta todos los archivos(contenidos en el primer parametro), en la direccion
contenida en la estructura(segundo parametro)*/
int unpack_all(FILE*, option_args *args);

/*Lista por Nombre, Fecha de Ultima Modificacion y Peso(criterio especificado
en el tercer parametro, usando las macros declaradas arriba) todos los archivos
(contenidos en el promer parametro)*/
int list(FILE*, option_args *args, size_t);

/*Muestra los detalles completos de un archivo recibido contenido en la estructura
(segundo parametro), el cual se encuentra empaquetado(primer parametro)*/
int detail(FILE*, option_args *args);

/*Determina si el formato del archivo de entrada es correcto*/
void ok_input(FILE*, const char*);

/*Determina si el nombre del archivo de salida es correcto*/
void ok_output(char*);

/*Determina si existe el archivo(segundo parametro) dentro del directorio(primer parametro)
antes de escribirlo, de existir pregunta si se quiere cambiar el nombre, si se quiere
sobrescribir o si no se debe hacer nada(se cerrara el programa).
El tercer parametro indica si es un paquete o un archivo, de ser un paquete
comprueba si existe y luego el nombre con la funcion ok_output, de ser de archivos
desempaquetados solo comprueba si existe*/
void file_exist(const char*, char*, size_t);
#endif
