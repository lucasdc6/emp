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

#include "headers.h" /*Funciones que trabajan con los headers*/
#include "empTypes.h" /*Tipos usados en el paquete*/
#include <stdio.h> /*Entrada/Salida*/
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "error.h"
#include "oper.h"
#include "args.h"

int small_pack(FILE* output, char *arg_pack){
	printf("Packing \"%s\"...\n", arg_pack);
	FILE* pack; //Archivo a empaquetar
	int c;
	t_head_file regf;
	create_head_file(&regf, arg_pack);
	write_head_file(output, &regf);
	if ((pack = fopen(arg_pack, "r+")) == NULL){
		errors_2p(output, NULL, "ERROR opnening", arg_pack, OPEN, 1, 0);
	}
	else{
		while((c = fgetc(pack)) != EOF){
			if(fputc(c, output) == EOF){
				fclose(pack);
				errors_2p(output, NULL, "ERROR writing", arg_pack, WRITE, 0, 1);
			}
		}
		if(errno != 0){
			fclose(pack);
			errors_2p(output, NULL, "ERROR reading", arg_pack, READ, 0, 1);
		}
	}
	fclose(pack);
	return printf("Packed \"%s\"\n\n", arg_pack);
}

int pack_dir(FILE* output, const char* dir){
	int ret = 0;
	char dire[MAX_PATH];
	struct dirent *direntp;
	struct stat buf;
	DIR* directory;
	if((directory = opendir(dir)) == NULL){
		closedir(directory);
		errors_2p(output, NULL, "ERROR to open the directory", dir, OPEN_DIR, 0, 1);
	}
	while((direntp = readdir(directory)) != NULL){
		if(strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, "..")){
			strcpy(dire, dir);
			if(dire[strlen(dire)-1] != '/'){
				strcat(dire, "/");
			}
			strcat(dire, direntp->d_name);
			ret++;
			if(stat(dire, &buf) != 0){
				closedir(directory);
				errors_2p(output, NULL, "ERROR opnening", dire, OPEN, 0, 1);
			}
			else{
				if(S_ISDIR(buf.st_mode)){
					ret += pack_dir(output, dire);
					if(ret) ret--;
				}
				if(S_ISREG(buf.st_mode)){
					small_pack(output, dire);
				}
			}
		}
	}
	closedir(directory);
	return ret; //Cantidad de archivos empaquetados
}

int big_pack(FILE* output, option_args *args){
	t_head reg;
	create_head(&reg);
	write_head(output, &reg);
	int i, c, f_dir = 0; //Cantidad de archivos en directorios
	struct stat buf;
	for(i = 0; i < args->operands.cant; i++){
		if(stat(args->operands.list[i], &buf) != 0){
			remove(args->operands.out);
			errors_2p(output, args, "ERROR opnening", args->operands.list[i], OPEN, 0, 0);
		}
		if(S_ISDIR(buf.st_mode)){
			f_dir += pack_dir(output, args->operands.list[i]);
			if(!f_dir){
				remove(args->operands.out);
				errors_msg(output, args, "No files in directory", NO_FILES, 0, 0);
			}
			if(f_dir) f_dir--;
		}
		if(S_ISREG(buf.st_mode)){
			small_pack(output, args->operands.list[i]);
		}
	}
	if ((c = fseek(output, 4, SEEK_SET)) == -1){
		remove(args->operands.out);
		errors_1p(output, args, "ERROR to set the cursor", WRITE, 0, 0);
	}
	else{
		uint32_t head_entries;
		read_item(output, &head_entries, sizeof(uint32_t), 1);
		head_entries += args->operands.cant + f_dir;
		if ((c = fseek(output, 4, SEEK_SET)) == -1){
			remove(args->operands.out);
			errors_1p(output, args, "ERROR to set the cursor", WRITE, 0, 0);
		}
		else{
			write_item(output, &head_entries, sizeof(uint32_t), 1);
		}
	}
	fclose(output);
	return printf("Packed files into %s\n", args->operands.out);
}

int repack(FILE* output, option_args *args){
	int i, c, f_dir = 0; //Cantidad de archivos en directorios
	struct stat buf;
	for(i = 0; i < args->operands.cant; i++){
		if(stat(args->operands.list[i], &buf) != 0){
			remove(args->operands.out);
			errors_2p(output, args, "ERROR opnening", args->operands.list[i], OPEN, 0, 0);
		}
		if(S_ISDIR(buf.st_mode)){
			f_dir += pack_dir(output, args->operands.list[i]);
			if(!f_dir){
				remove(args->operands.out);
				errors_msg(output, args, "No files in directory", NO_FILES, 0, 0);
			}
			if(f_dir) f_dir--;
		}
		if(S_ISREG(buf.st_mode)){
			small_pack(output, args->operands.list[i]);
		}
	}
	fclose(output);
	if ((output = fopen(args->operands.out, "r+")) == NULL){
		errors_2p(output, args, "ERROR opnening", args->operands.out, OPEN, 0, 0);
	}
	if ((c = fseek(output, 4, SEEK_SET)) == -1){
		remove(args->operands.out);
		errors_1p(output, args, "ERROR to set the cursor", WRITE, 0, 0);
	}
	else{
		uint32_t head_entries;
		read_item(output, &head_entries, sizeof(uint32_t), 1);
		head_entries += args->operands.cant + f_dir;
		if ((c = fseek(output, -4, SEEK_CUR)) == -1){
			remove(args->operands.out);
			errors_1p(output, args, "ERROR to set the cursor", WRITE, 0, 0);
		}
		else{
			write_item(output, &head_entries, sizeof(uint32_t), 1);
		}
	}
	fclose(output);
	return printf("Repacked files into %s\n", args->operands.out);
}

static int mk_dir(const char *dir, int mode){
	if(mkdir(dir, mode) == -1){
		return 1;
	}
	else{
		printf("Creating directory \"%s\"...\n", dir);
		errno = 0; //Reseteo errno seteado por opendir, error ya resuelto
		return 0;
	}
}

static void make_directories(const char* dir){
	int i;
	char aux[strlen(dir)+1];
	DIR* directory;
	for(i = 0; i < strlen(dir); i++){
		if(dir[i] == '/' && i > 1){
			strncpy(aux, dir, i);
			aux[i] = '\0';
			if((directory = opendir(aux)) == NULL){
				if(mk_dir(aux, 0777) == 1){
					errors_2p(NULL, NULL, "ERROR creating the directory", aux, CREATE, 1, 1);
				}
			}
			else
				closedir(directory);
		}
	}
	if((directory = opendir(dir)) == NULL){
		if(mk_dir(dir, 0777) == 1){
			errors_2p(NULL, NULL, "ERROR creating the directory", aux, CREATE, 1, 1);
		}
	}
	else
		closedir(directory);
}

static int small_unpack(FILE* input, const char* arg_unpack, const char* d_input, const int tam, const char* path){
	FILE* output;
	char *last = strrchr(path,'/');
	char aux[MAX_PATH];
	char dir[MAX_PATH];
	strcpy(dir, arg_unpack);
	if(dir[strlen(dir)-1] != '/'){
		strcat(dir, "/");
	}
	char o_path[MAX_PATH];
	strcpy(o_path, path);
	file_exist(dir, o_path, 1);
	strcat(dir, o_path);
	if (last != NULL){
		strcpy(aux, arg_unpack);
		if(aux[strlen(aux)-1] != '/'){
			strcat(aux, "/");
		}
		strncat(aux, path, last - path);
		make_directories(aux);
		strcpy(o_path, strrchr(path, '/')+1);
		file_exist(aux, o_path, 1);
	}
	printf("Unpacking \"%s\"...\n", dir);
	if((output = fopen(dir, "w")) == NULL){
		errors_2p(input, NULL, "ERROR creating the directory", dir, CREATE, 0, 1);
	}
	else{
		int k, c;
		for(k = 1; k <= tam; k++){
			if((c = fgetc(input)) != EOF){
				if((fputc(c, output)) == EOF){
					fclose(output);
					errors_2p(input, NULL, "ERROR writing", d_input, WRITE, 0, 1);
				}
			}
			else{
				fclose(output);
				errors_2p(input, NULL, "ERROR reading", dir, READ, 0, 1);
			}
		}
	fclose(output);
	}
	return printf("Unpacked \"%s\"\n\n", dir);
}

int unpack(FILE* input, option_args *args){
	char dir[strlen(args->operands.out)+1];
	strcpy(dir, args->operands.out);
	DIR* directory;
	t_head head_p;
	t_head_file reg;
	int i, j;
	size_t files[args->operands.cant];
	if((directory = opendir(dir)) == NULL){
		if(mk_dir(dir, 0777) == 1){
			errors_2p(input, args, "ERROR creating the directory", dir, CREATE, 0, 0);
		}
	}
	read_head(input, &head_p);
	for(i = 1; i <= head_p.entries; i++){
		read_head_file(input, &reg);
		for(j = 0; j < args->operands.cant; j++){
			if (strcmp(args->operands.list[j], reg.path) == 0){
				small_unpack(input, args->operands.out, args->operands.in, reg.tam, reg.path);
				files[j] = 1;
				break;
			}
		}
		if(files[j] != 1){
			if ((fseek(input, reg.tam, SEEK_CUR)) != 0){
					errors_1p(input, args, "ERROR to set the cursor", CUR, 0, 0);
			}
		}
	}
	for(i = 0; i < args->operands.cant; i++){
		if(files[i] != 1) fprintf(stderr, "Can't find the file \"%s\"\n", args->operands.list[i]);
	}
	free(reg.path);
	closedir(directory);
	fclose(input);
	return printf("Unpacked files from \"%s\" to \"%s\"\n", args->operands.in, dir);
}


int unpack_all(FILE* input, option_args *args){
	DIR* directory;
	t_head head_p;
	t_head_file reg;
	int i;
	if((directory = opendir(args->operands.out)) == NULL){
		if(mk_dir(args->operands.out, 0777) == 1){
			errors_2p(input, args, "ERROR creating the directory", args->operands.out, CREATE, 0, 0);
		}
	}
	read_head(input, &head_p);
	for(i = 1; i <= head_p.entries; i++){
		read_head_file(input, &reg);
		small_unpack(input, args->operands.out, args->operands.in, reg.tam, reg.path);
		free(reg.path);
	}
	closedir(directory);
	fclose(input);
	return printf("Unpacked all files from \"%s\" to \"%s\"\n", args->operands.in, args->operands.out);
}

int detail(FILE* input, option_args *args){
	struct tm *tm;
	char buf[MAX_PATH];
	t_head head_p;
	t_head_file reg;
	read_head(input, &head_p);
	int i;
	size_t ok = 0;
	for (i = 0; i < head_p.entries; i++){
		read_head_file(input, &reg);
		if ((strcmp(reg.path, args->operands.list[0])) == 0){
			ok = 1;
			tm = localtime(&reg.date);
			strftime(buf, sizeof(buf), "%Y.%m.%d %H:%M:%S", tm);
			printf("Path: %s\nDate of last modification: %s\nSize: %llu bytes\n\n", reg.path, buf, reg.tam);
			break;
		}
		else{
			if ((fseek(input, reg.tam, SEEK_CUR)) != 0){
				errors_1p(input, args, "ERROR to set the cursor", CUR, 0, 0);
			}
		}
		free(reg.path);
	}
	if (!ok){
		fprintf(stderr, "Could not find file \"%s\" in \"%s\"\n", args->operands.list[0], args->operands.in);
		fclose(input);
		free_files_array(&args->operands);
		free(args);
		exit(NO_FILES);
	}
	else{
		free(reg.path);
	}
	fclose(input);
	return printf("Details of file \"%s\" from \"%s\"\n", args->operands.list[0], args->operands.in);
}

static int compare_size(const void * p1, const void * p2){
	t_head_file * r1 = (t_head_file*)p1;
	t_head_file * r2 = (t_head_file*)p2;
	if (r1->tam < r2->tam) return -1;
	else if (r1->tam > r2->tam) return 1;
	else return 0;
}

static int compare_date(const void * p1, const void * p2){
	t_head_file * r1 = (t_head_file*)p1;
	t_head_file * r2 = (t_head_file*)p2;
	if (r1->date < r2->date) return -1;
	else if (r1->date > r2->date) return 1;
	else return 0;
}

static int compare_str(const void * p1, const void * p2){
	t_head_file * r1 = (t_head_file*)p1;
	t_head_file * r2 = (t_head_file*)p2;
	return strcmp(r1->path, r2->path);
}

int list(FILE* input, option_args *args, const size_t type){
	int i;
	t_head head_p;
	t_head_file reg;
	read_head(input, &head_p);
	t_head_file files[head_p.entries]; //debe ser de longitud fija para utilizar el qsort
	for(i = 0; i < head_p.entries; i++){
		read_head_file(input, &reg);
		files[i] = reg;
		if ((fseek(input, reg.tam, SEEK_CUR)) != 0){
				errors_1p(input, args, "ERROR to set the cursor", CUR, 0, 0);
		}
	}
	switch(type){
		case NAME:
			qsort(files, head_p.entries, sizeof(t_head_file), &compare_str);
			for(i = 0; i < head_p.entries; i++){
				printf("%s\n", files[i].path);
				free(files[i].path);
			}
			break;
		case DATE:
			qsort((void*)files, head_p.entries, sizeof(t_head_file), &compare_date);
			for(i = 0; i < head_p.entries; i++){
				printf("%s %lu\n", files[i].path, files[i].date);
				free(files[i].path);
			}
			break;
		case SIZE:
			qsort((void*)files, head_p.entries, sizeof(t_head_file), &compare_size);
			for(i = 0; i < head_p.entries; i++){
				printf("%s %llu\n", files[i].path, files[i].tam);
				free(files[i].path);
			}
			break;
	}
	fclose(input);
	return printf("Listing files by %s to %s\n", args->operands.list[0], args->operands.in);
}

void ok_input(FILE* input, const char* in){
	struct stat buf;
	if(stat(in, &buf) != 0){
		remove(in);
		errors_2p(input, NULL, "ERROR opnening", in, OPEN, 0, 1);
	}
	if(buf.st_size < 24){
		remove(in);
		errno = ECANCELED; //errno = Operación cancelada
		errors_2p(input, NULL, "ERROR Incorrect format of the file of input", in, FORMAT, 0, 1);
	}
	t_head head;
	read_head(input, &head);
	if(strncmp(head.magic, "EMP", 3) != 0){
		remove(in);
		errno = ECANCELED; //errno = Operación cancelada
		errors_2p(input, NULL, "ERROR Incorrect format of the file of input", in, FORMAT, 0, 1);
	}
}

void ok_output(char* out){
	if(strstr(out, ".emp") == NULL){
		strcat(out, ".emp");
	}
	else{
		if(strlen(out) <= 4){
			fprintf(stderr, "The name cannot be blank.\nDo you want to change the name? Y/N\n");
			char op[1];
			size_t ok_op = 0;
			scanf("%s", op);
			do{
				if(!strcmp(op, "y") || !strcmp(op, "Y")){
					printf("Enter the new name\n");
					scanf("%s", out);
					ok_op = 1;
					ok_output(out);
				}
				if(!strcmp(op, "n") || !strcmp(op, "N")){
					fprintf(stderr, "Program stopped\n");
					exit(W_NAME);
				}
				fprintf(stderr, "Wrong option.\n");
			}
			while(ok_op);
			//ok_output(out);
		}
	}
}

void file_exist(const char* dir, char* path, size_t io){
	DIR* directory;
	struct dirent *direntp;
	if((directory = opendir(dir)) == NULL){
		closedir(directory);
		errors_2p(NULL, NULL, "ERROR to open the directory", dir, OPEN_DIR, 1, 1);
	}
	while((direntp = readdir(directory)) != NULL){
			if(!strcmp(direntp->d_name, path)){
				fprintf(stderr, "Already exist a file named \"%s\"\nDo you want to change the name? Y/N\n", path);
				char op[1];
				scanf("%s", op);
				if(!strcmp(op, "y") || !strcmp(op, "Y")){
					printf("Enter the new name\n");
					scanf("%s", path);
					if(!io) ok_output(path);
					file_exist(dir, path, io);
					break;
				}
				if(!strcmp(op, "n") || !strcmp(op, "N")){
					fprintf(stderr, "Do you want to rewrite the existing file? Y/N\n");
					scanf("%s", op);
					if(!strcmp(op, "y") || !strcmp(op, "Y")) break;
					if(!strcmp(op, "n") || !strcmp(op, "N")){
						static char ok = '2';
						char ok2[1];
						strcpy(ok2, "2");
						if(ok == '2'){
							if(!io){
								path[strlen(path)-4] = '(';
								path[strlen(path)-3] = ok++;
								path[strlen(path)-2] = ')';
								path[strlen(path)-1] = '\0';
							}
							else{
								strcat(path, "(");
								strcat(path, ok2);
								strcat(path, ")");
								ok++;
							}
						}
						else{
							if(ok <= '9'){
								if(!io){
									path[strlen(path)-7] = '(';
									path[strlen(path)-6] = ok++;
									path[strlen(path)-5] = ')';
								}
								else{
									path[strlen(path)-3] = '(';
									path[strlen(path)-2] = ok++;
									path[strlen(path)-1] = ')';
								}
							}
							else{
								printf("\nThat was a lot of enters!\nSpecifically 9\nThe number don't pass the 9\n");
								closedir(directory);
								exit(99);
							}
						}
						if(!io) ok_output(path);
						fprintf(stderr, "New name = \"%s\"\n", path);
						file_exist(dir, path, io);
						break;
					}
				}
				fprintf(stderr, "Wrong option.\n");
				file_exist(dir, path, io);
				break;
			}
	}
	closedir(directory);
}
