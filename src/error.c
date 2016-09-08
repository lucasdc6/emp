#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <zlib.h>
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

void zerr(int ret){
    fputs("zpipe: ", stderr);
    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            fputs("ERROR reading stdin\n", stderr);
        if (ferror(stdout))
            fputs("ERROR writing stdout\n", stderr);
        break;
    case Z_STREAM_ERROR:
        fputs("ERROR invalid compression level\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("ERROR invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("ERROR out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("ERROR zlib version mismatch!\n", stderr);
    }
}
