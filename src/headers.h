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

#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include "empTypes.h"

/*Generate the principal header from the package with all the default values

Genera el encabezado principal del paquete con todos los datos seteados predeterminadamente
Magic = EMP
Version = 1
Entradas = 0
Reservado 1 y 2 = 0
*/
int create_head(t_head *);

/*Generate the principal header from each file in the package, receives the path
of the file to determinate the size and the date of the last modification.

Genera el encabezado principal de cada archivo, recibe el path del archivo
para determinar el Tamaño y la Fecha de Ultima Modificacion*/
int create_head_file(t_head_file *, const char*);

/*Write just one item of the structure

Escribe un solo campo de la estructura*/
void write_item(FILE*, void*, uint32_t, size_t);

/*Write at the principal file the principal header

Escribe al archivo principal el header principal*/
int write_head (FILE*, t_head*);

/*Write at the principal file the header from each file
in the package

Escribe al archivo el header para cada archivo del paquete*/
int write_head_file(FILE*, t_head_file*);

/*Read one item from the file

Lee un solo campo del archivo*/
void read_item(FILE*, void*, uint32_t, size_t);

/*Read the principal structure of the file. The function need the cursor at
the beginning

Lee la estructura principal del archivo, ya se debe posicionar el puntero del
archivo antes de llamar la funcion*/
int read_head(FILE*, t_head*);

/*Read the principal structure from each file packed. The function needs the cursor 
correctly setted

Lee la estructura de cada archivo empaquetado del archivo, ya se debe posicionar
el puntero del archivo antes de llamar la funcion*/
int read_head_file(FILE*, t_head_file*);

#endif
