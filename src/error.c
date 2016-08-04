#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "args.h"
#include "empTypes.h"
#include "oper.h"

extern clock_t start;

void errors_2p(FILE* file, option_args *args, const char* msg, const char* path, const int num_err, size_t ok_file, size_t ok_args){
	fprintf(stderr, "%s \"%s\": %s\n", msg, path, strerror(errno));
	if(!ok_args){
		free_files_array(&args->operands);
		free(args);
	}
	if(!ok_file) fclose(file);
	print_time(start, 1);
	exit(num_err);
}

void errors_1p(FILE* file, option_args *args, const char* msg, const int num_err){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	free_files_array(&args->operands);
	free(args);
	fclose(file);
	print_time(start, 1);
	exit(num_err);
}

void errors_msg(FILE* file, option_args *args, const char* msg, const int num_err, size_t ok_file, size_t ok_args){
	fprintf(stderr, "%s\n", msg);
	if(!ok_args){
		free_files_array(&args->operands);
		free(args);
	}
	if(!ok_file) fclose(file);
	print_time(start, 1);
	exit(num_err);
}
