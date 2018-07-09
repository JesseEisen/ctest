#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "list.h"

typedef struct Funcinfo Funcinfo;
struct Funcinfo{
	list_head  node;
	char       *funcname;
};


/*
 * step1: read test file and append each function into test list;
 * step2: compile the test file into a libxxx.so file;
 * step3: use dlopen to get function and execute it teardown;
 * step4: report the result
 */

void
gathertest(char *file)
{
	FILE *fp;

	fp = fopen(file,"r");
	if(fp == NULL)
		return;


}


void 
readfile(int nfile, char **files)
{
	int i;

	for(i=0; i < nfile; i++){
		gathertest(files[i]);
	}
}


int 
main(int argc, char **argv)
{
	if(argc < 1){
		fprintf(stderr, "Usage: %s [files]\n", argv[0]);
		return 0;
	}

	readfile(argc, argv);
}
