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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "empTypes.h"
#include "error.h"
#include "args.h"
#include "oper.h"

clock_t start;

int main(int argc, char *argv[]){
    start = clock();
	option_args *args;
	args = parse(argc, argv);
	switch(args->op_index){
	case OP_PACK:
		if (args->operands.num_out == 1){
			ok_output(args->operands.out);
			file_exist("./", args->operands.out, 0);
			FILE* output;
			if ((output = fopen(args->operands.out, "w+")) == NULL){
				errors_2p(output, args, "ERROR creating", args->operands.out, CREATE, 0, 0);
      		}
			big_pack(output, args);
		}
		else{
			errors_msg(NULL, args, "ERROR Enter an output package", OP_OUT, 1, 0);
		}
		break;
	case OP_UNPACK:;
		FILE* input;
		if ((input = fopen(args->operands.in, "r")) == NULL){
			errors_2p(input, args, "ERROR opening", args->operands.in, OPEN, 0, 0);
		}
		ok_input(input, args->operands.in);
		rewind(input);
		if(args->operands.num_out == 1){
			unpack(input, args);
		}
		else{
			strcpy(args->operands.out, "./");
			unpack(input, args);
		}
		break;
	case OP_REPACK:
		if (args->operands.num_out == 1){
			FILE* output;
			ok_output(args->operands.out);
			if ((output = fopen(args->operands.out, "a+")) == NULL){
				errors_2p(output, args, "ERROR opnening", args->operands.out, OPEN, 0, 0);
      		}
      		ok_input(output, args->operands.out);
			repack(output, args);
		}
		else{
			errors_msg(NULL, args, "ERROR: enter an output package", OP_OUT, 1, 0);
		}
		break;
	case OP_UNPACKALL:
		if(args->operands.num_in != 1){
			errors_msg(NULL, args, "ERROR: enter an input package", OP_IN, 1, 0);
		}
		else{
			FILE* input;
			if ((input = fopen(args->operands.in, "r")) == NULL){
				errors_2p(input, args, "ERROR opnening", args->operands.in, OPEN, 0, 0);
			}
			ok_input(input, args->operands.in);
			rewind(input);
			if(args->operands.num_out == 1){
				unpack_all(input, args);
			}
			else{
				strcpy(args->operands.out, "./"); //Seteo de direccion predeterminada
				unpack_all(input, args);
			}
		}
		break;
	case OP_DETAIL:
		if(args->operands.num_in == 1 && args->operands.cant == 1){
			FILE* input;
			if ((input = fopen(args->operands.in, "r")) == NULL){
				errors_2p(input, args, "ERROR opnening", args->operands.in, OPEN, 0, 0);
			}
			ok_input(input, args->operands.in);
			rewind(input);
			detail(input, args);
		}
		else{
			if(args->operands.num_in == 0){
				errors_msg(NULL, args, "ERROR: enter an input package", OP_IN, 1, 0);
			}
			else{
				errors_msg(NULL, args, "ERROR: enter a single file", NUM_FILES, 1, 0);
			}
		}
		break;
	case OP_LIST:
		if ((input = fopen(args->operands.in, "r")) == NULL){
			errors_2p(input, args, "ERROR opnening", args->operands.in, OPEN, 0, 0);
		}
		ok_input(input, args->operands.in);
		rewind(input);
		if(args->operands.cant == 1 && args->operands.num_in == 1){
			if(strcmp(args->operands.list[0], "name") == 0){
				list(input, args, NAME);
			}
			else{
				if(strcmp(args->operands.list[0], "date") == 0){
					list(input, args, DATE);
				}
				else{
					if(strcmp(args->operands.list[0], "size") == 0){
						list(input, args, SIZE);
					}
					else{
						errors_msg(input, args, "ERROR: enter a single file", OP_LIS_INC, 0, 0);
					}
				}
			}
		}
		else{
			if(args->operands.cant == 0){
				printf("Default option = NAME\n\n");
				args->operands.list[0] = (char*) malloc(5);
				strcpy(args->operands.list[0], "name");
				list(input, args, NAME);
				free(args->operands.list[0]);
			}
		}
		break;
	}
	free_files_array(&args->operands);
	free(args);
	print_time(start, 1);
	return 0;
}
