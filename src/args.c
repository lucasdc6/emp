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
along with EMP. If not, see <http://www.gnu.org/licenses/>.	*/

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "empTypes.h"
#include "args.h"
#include "error.h"

#define V "0.2"

char *longopts[] = {
	"--pack",
	"--unpack",
	"--repack",
	"--unpack-all",
	"--detail",
	"--list"
};

char *longio[] = {
	"--input",
	"--output",
	"--outputdir"
};

char *shortopts[] = {
	"-p",
	"-u",
	"-r",
	"-a",
	"-d",
	"-l"
};

char *shortio[] = {
	"-i",
	"-o",
	"-t"
};

static void version(){
	printf("EMP %s\nCopyright (C) 2016 Free Software Foundation, Inc.\nLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Lucas Di Cunzolo\n", V);
	exit(0);
}

static void help(const char *progname){
	printf("Use:\n");
	printf("\t%s --pack file1.txt --output file.emp [--compress][--silent]\n", progname);
	printf("\t%s --unpack file1.txt --input file.emp[--outputdir /tmp][--compress][--silent]\n", progname);
	printf("\t%s --repack file2.bin --output file.emp [--compress][--silent]\n", progname);
	printf("\t%s --unpack-all --input file.emp [--outputdir /tmp][--compress][--silent]\n", progname);
	printf("\t%s --detail file1.txt --input file.emp [--silent]\n", progname);
	printf("\t%s --list [name|date|size] --input file.emp [--silent]\n", progname);
	printf("\nOther options:\n");
	printf("\t%s --version \t- print the program version\n", progname);
	printf("\t%s --help \t- print this help\n", progname);
}

static void error(const char *msg, const int err){
	fprintf(stderr, "%s\n", msg);
	exit(err);
}

static void init_files_array(files_array *a, int initial_size, int initial_tam){
	a->list = (char**)malloc((initial_tam+1) * sizeof(a->list));
	a->in = (char*)malloc((initial_size) * sizeof(char));
	a->out = (char*)malloc((initial_size) * sizeof(char));
	a->cant = 0;
	a->compress = 0;
	a->silent = 0;
	a->size = initial_size;
	a->list_size = initial_tam;
	a->num_in = 0;
	a->num_out = 0;
}

static void insert_name_files(files_array *a, char* file){
	if(a->cant == a->list_size){
		a->list_size *= 2;
		a->list = (char**)realloc(a->list, (a->list_size+1) * sizeof(a->list));
	}
	a->list[a->cant] = (char*)malloc(strlen(file)+1);
	strcpy(a->list[a->cant++], file);
}

void free_files_array(files_array *a){
	int i;
	for(i = 0; i < a->cant; i++){
		free(a->list[i]);
	}
	free(a->list);
	free(a->in);
	free(a->out);
	a->cant = 0;
	a->compress = 0;
	a->silent = 0;
	a->size = 0;
	a->list_size = 0;
	a->num_in = 0;
	a->num_out = 0;
}

option_args *parse(int argc, char** argv){
	if(argc == 2){
		if(!strcmp(argv[1], "--version")){
			version();
		}
		if(!strcmp(argv[1], "--help")){
			help(argv[0]);
			exit(0);
		}
	}
	if (argc < 4){
		if(argc > 1) fprintf(stderr, "The minimum of arguments is 4\n\n");
		help(argv[0]);
		exit(NO_OPERATIONS);
	}
	option_args *optargs = malloc(sizeof(option_args));
	strcpy(optargs->option, "no");
	optargs->num_op = 0;
	init_files_array(&optargs->operands, 32, 10);
	int operands = 0, i;
	for(i = 1; i < argc; i++){
		int optindex;
		unsigned short is_operation = 0;
		for(optindex = 0; optindex < OPTLEN; optindex++){
			if(strcmp(argv[i], longopts[optindex]) == 0 || strcmp(argv[i], shortopts[optindex]) == 0){
				optargs->num_op++;
				if(optargs->num_op > 1){
					error("You can't specify more than one option", NO_OPERATIONS);
				}
				is_operation = 1;
				strcpy(optargs->option, shortopts[optindex]);
				optargs->op_index = optindex;
				break;
			}
		}
		if(strcmp(argv[i], longio[0]) == 0 || strcmp(argv[i], shortio[0]) == 0){
			optargs->operands.num_in ++;
			if(optargs->operands.num_in > 1){
				error("You can't specify more than one input file", OP_IN);
			}
			if(i+1 == argc){
				error("Please specify an input file", OP_IN);
			}
			else{
				strcpy(optargs->operands.in, argv[++i]);
			}
			continue;
		}
		if(strcmp(argv[i], longio[1]) == 0 || strcmp(argv[i], shortio[1]) == 0){
			optargs->operands.num_out++;
			if(optargs->operands.num_out > 1){
				error("You can't specify more than one output file", OP_OUT);
			}
			if(i+1 == argc){
				error("Please specify an output file", OP_IN);
			}
			else{
				strcpy(optargs->operands.out, argv[++i]);
			}
			continue;
		}
		else{
			if(strcmp(argv[i], longio[2]) == 0 || strcmp(argv[i], shortio[2]) == 0){
				optargs->operands.num_out++;
				if(optargs->operands.num_out > 1){
					error("You can't specify more than one output file", OP_OUT);
				}
				if(i+1 == argc){
					error("Please specify an output file", OP_IN);
				}
				else{
					strcpy(optargs->operands.out, argv[++i]);
				}
				continue;
			}
		}
		if(strcmp(argv[i], "--compress") == 0 || strcmp(argv[i], "-c") == 0){
				optargs->operands.compress = 1;
				continue;
		}
		if(strcmp(argv[i], "--silent") == 0 || strcmp(argv[i], "-s") == 0){
			optargs->operands.silent = 1;
			continue;
		}
		if (optindex == OPTLEN && !is_operation){
			if(optargs->num_op != 0){
				operands++;
				insert_name_files(&optargs->operands, argv[i]);
			}
			else{
				help(argv[0]);
				free_files_array(&optargs->operands);
				free(optargs);
				printf("\n");
				error("You can't specify a file before an option", NO_OPERATIONS);
			}
		}
	}
	return optargs;
}
