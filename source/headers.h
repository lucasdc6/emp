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

/*Genera el encabezado principal del paquete con todos los datos seteados predeterminadamente
Magic = EMP
Version = 1
Entradas = 0
Reservado 1 y 2 = 0
*/
int create_head(t_head *);

/*Genera el encabezado principal de cada archivo, recibe el path del archivo
para determinar el Tamaño y la Fecha de Ultima Modificacion*/
int create_head_file(t_head_file *, const char*);

void write_item(FILE*, void*, uint32_t, size_t);

/*Carga al archivo principal el header principal*/
int write_head (FILE*, t_head*);

/*Carga al archivo el header para cada archivo del paquete*/
int write_head_file(FILE*, t_head_file*);

void read_item(FILE*, void*, uint32_t, size_t);

/*Lee el registro principal del archivo, ya se debe posicionar el puntero del
archivo antes de llamar la funcion*/
int read_head(FILE*, t_head*);

/*Lee el registro de cada archivo empaquetado del archivo, ya se debe posicionar
el puntero del archivo antes de llamar la funcion*/
int read_head_file(FILE*, t_head_file*);

#endif
