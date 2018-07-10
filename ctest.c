#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "list.h"

#define MAXARGS 20

struct list_head  namelist;

typedef struct Funcinfo Funcinfo;
struct Funcinfo{
	struct list_head  node;
	char       		 *funcname;
};

void 
ctestinit(void)
{
	INIT_LIST_HEAD(&namelist);
}


char* 
lefttrim(char *s)
{
	int len = strlen(s);
	char *cur = s;

	while(*cur && isspace(*cur)){
		cur++;
		--len;
	}

	if(s != cur) memmove(s, cur, len+1);

	return s;
}

char* 
righttrim(char *s)
{
	int len = strlen(s);
	char *cur = s + len - 1;
	short is_space;

	while(cur != s && (isspace(*cur) || *cur == '\n'))
		--cur;

	is_space = (isspace(*cur) || *cur == '\n');
	cur[is_space ? 0 : 1] = '\0';

	return s;
}



char* 
strtrim(char *s)
{
	s = lefttrim(s);
	s = righttrim(s);

	return s;
}


/*
 * step1: read test file and append each function into test list;
 * step2: compile the test file into a libxxx.so file;
 * step3: use dlopen to get function and execute it teardown;
 * step4: report the result
 */

void
parseline(char *buffer, size_t len)
{
	char *start, *end, *funcname;
	Funcinfo  *fi = malloc(sizeof(Funcinfo));
		
	if((start = strstr(buffer, "Test_")) == NULL)
		return;

	/* start of line or behind the type */
	if((start == buffer) || *(--start) == ' '){
		end = strchr(buffer, '(');
		if(end != NULL && *(end-1) == ' ')
			end--;
		else if(end == NULL)
			return;
		
		funcname = strndup(start, end-start);
		funcname = strtrim(funcname);
		fi->funcname = funcname;
		list_add(&fi->node, &namelist);
	}else{
		//do nothing
	}

}


void
gathertest(char *file)
{
	FILE  *fp;
	char  *line;
	size_t linesize = 100;
	size_t chars = 0;

	fp = fopen(file,"r");
	if(fp == NULL)
		return;
	
	line = malloc(linesize * sizeof(char));
	if(line == NULL)  return;

	while((chars=getline(&line, &linesize, fp)) != -1){
		parseline(line, chars);
	}

	fclose(fp);
}

int
istestfile(char *filename)
{
	return strncmp(filename, "Test_", 5);
}


void 
readfile(int nfile, char **files)
{
	int i;
	
	for(i=0; i<nfile; i++){
		if(istestfile(files[i]) == 0)
			gathertest(files[i]);
	}
}


void
showfuncname(void)
{
	Funcinfo *fi, *fitemp;

	list_for_each_entry_safe(fi, fitemp, &namelist, node){
		printf("%s\n", fi->funcname);
		list_del(&fi->node);
		free(fi->funcname);
		free(fi);
	}

}

void
compilefile(int argc, char **argv)
{
	pid_t  pid;

	char *args[MAXARGS] = {"gcc", "-fPIC", "-shared", "-o", "libtest.so"};
	int i = 5;

	for(; i<argc+5; i++){
		args[i] = argv[i-4];
	}

	args[i] = NULL;

	if((pid=fork()) < 0)
		return;
	else if(pid == 0)
		execvp(args[0], args);
	else
		waitpid(pid, NULL, 0);
}

void
lookupsym()
{
	Funcinfo  *fi;
	void      *fptr;
	void *h = dlopen("./libtest.so", RTLD_NOW | RTLD_GLOBAL);
	
	list_for_each_entry(fi, &namelist, node){
		printf("%s\n", fi->funcname);
		fptr = dlsym(h, fi->funcname);
		void (*f)() = fptr;
		f();
	}

	dlclose(h);
}


int 
main(int argc, char **argv)
{
	if(argc < 1){
		fprintf(stderr, "Usage: %s [files]\n", argv[0]);
		return 0;
	}

	ctestinit();
	readfile(argc, argv);

	compilefile(argc, argv);
	printf("lookup symbol\n");
	lookupsym();
	
	showfuncname();

	return 0;
}
