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

#include "empTypes.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "error.h"

int create_head(t_head *reg){
	reg->magic[0] = 'E';
	reg->magic[1] = 'M';
	reg->magic[2] = 'P';
	reg->version = 1;
	reg->entries = 0;
	reg->reserv1 = 0;
	reg->reserv2 = 0;
	return 0;
}

int create_head_file(t_head_file *reg, const char *arg_path){
	struct stat sb;
	stat(arg_path, &sb);
	reg->tam = sb.st_size;
	reg->date = sb.st_mtime;
	reg->reserv1 = 0;
	reg->reserv2 = 0;
	reg->path = malloc(strlen(arg_path)+1);
	reg->path = strcpy(reg->path, arg_path);
	return 0;
}

void write_item(FILE *pk, void *item, uint32_t size, size_t cant){
	if(fwrite(item, size, cant, pk) == 0){
		fprintf(stderr, "Error writing the file: %s\n", strerror(errno));
		fclose(pk);
		exit(WRITE);
	}
}

int write_head(FILE *pk, t_head *reg){
	write_item(pk, &reg->magic, sizeof(char), 3);
	write_item(pk, &reg->version, sizeof(unsigned char), 1);
	write_item(pk, &reg->entries, sizeof(uint32_t), 1);
	write_item(pk, &reg->reserv1, sizeof(uint64_t), 1);
	write_item(pk, &reg->reserv2, sizeof(uint64_t), 1);
	return 0;
}

int write_head_file(FILE *pk, t_head_file *reg){
	write_item(pk, &reg->tam, sizeof(uint64_t), 1);
	write_item(pk, &reg->date, sizeof(time_t), 1);
	write_item(pk, &reg->reserv1, sizeof(uint64_t), 1);
	write_item(pk, &reg->reserv2, sizeof(uint64_t), 1);
	write_item(pk, reg->path, strlen(reg->path)+1, 1);
	return 0;
}

void read_item(FILE *pk, void *item, uint32_t size, size_t cant){
	if(fread(item, size, cant, pk) < cant){
		if(feof(pk)){
			errno = ECANCELED;
			fprintf(stderr, "ERROR Incorrect format of the file of input: The file needs more than the header\n%s\n", strerror(errno));
			fclose(pk);
			exit(FORMAT);
		}
		else
			errors_1p(pk, NULL, "Error reading the file", READ, 0, 1);
	}
}

int read_head(FILE *pk, t_head *reg){
	read_item(pk, &reg->magic, sizeof(char), 3);
	read_item(pk, &reg->version, sizeof(unsigned char), 1);
	read_item(pk, &reg->entries, sizeof(uint32_t), 1);
	read_item(pk, &reg->reserv1, sizeof(uint64_t), 1);
	read_item(pk, &reg->reserv2, sizeof(uint64_t), 1);
	return 0;
}

int read_head_file(FILE* pk, t_head_file *reg){
	read_item(pk, &reg->tam, sizeof(uint64_t), 1);
	read_item(pk, &reg->date, sizeof(time_t), 1);
	read_item(pk, &reg->reserv1, sizeof(uint64_t), 1);
	read_item(pk, &reg->reserv2, sizeof(uint64_t), 1);
	int c, i = 0;
	char aux[1024];
	while((c = fgetc(pk)) != '\0'){
		if(c == EOF){
			errors_1p(pk, NULL, "ERROR reading the file", READ, 0, 1);
		}
		aux[i++] = c;
	}
	aux[i] = '\0';
	reg->path = (char*)malloc(strlen(aux)+1);
	strcpy(reg->path, aux);
	return 0;
}
