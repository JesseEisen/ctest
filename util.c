#include "util.h"
#include "color.h"

#define INDENT "        "

static void
display_assertion(const char *filename, size_t assertion_line)
{
	FILE *file = fopen(filename, "r");
	char line[256];
	size_t line_number = 0;

	size_t padding = 2;
	size_t before_assertion = assertion_line - padding;
	size_t after_assertion = assertion_line + padding;

	bool not_last_line = false;

	while(line_number < after_assertion && (not_last_line = fgets(line, sizeof (line), file) != NULL)){

		line_number++;
		if (line_number < before_assertion || after_assertion < line_number)
			continue;

		if(line_number == assertion_line){
			char line_prefix[32];
			snprintf(line_prefix, sizeof (line_prefix), "> " COLOR_BOLD(MAGENTA, "%ld"), line_number);
			printf("    %19s", line_prefix);
			printf(" |  " COLOR_BOLD(CYAN, "%s"), line);
		}else{
			printf("    " COLOR(MAGENTA, "%6zu"), line_number);
			printf(" |  %s", line);
		}
	}

	if (!not_last_line)
		printf("\n");

	fclose(file);
}

/*
 * display the what you want to display
 */

static void
display_output(char *output)
{
	printf("Output:\n\n");

	char *pos = strchr(output, '\n');
	char *line = output;

	size_t line_number = 0;

	while(pos != NULL){
		line_number++;
		printf("    " COLOR(MAGENTA, "%6zu"), line_number);

		*pos = '\0';
		printf(" |  %s\n", line);
		*pos = '\n';

		line = pos + 1;
		pos = strchr(line, '\n');
	}

	printf("    " COLOR(MAGENTA, "%6zu"), line_number + 1);
	printf(" |  %s\n", line);
}

void
intequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
)
{
	if(expect != actual)
		display_assertion(fname, lineno);
	else
		display_output("passed");
}

void
intnequal
(
    int expect,
    int actual,
    int lineno,
    const char *fcname,
    const char *fname
)
{
	if(expect == actual)
		display_assertion(fname, lineno);
	else
		display_output("passed");
}

void
strequal
(
 	char* expect,
 	char* actual,
 	int lineno,
 	const char *fcname,
 	const char *fname
 )
{
	if((expect != NULL) && (actual != NULL)){
		if(strcmp(expect, actual) != 0)
			display_assertion(fname, lineno);
		else
			display_output("passed");
	}
}


void
strnequal
(
 	char* expect,
 	char* actual,
 	int lineno,
 	const char *fcname,
 	const char *fname
 )
{
	if((expect != NULL) && (actual != NULL)){
		if(strcmp(expect, actual) == 0)
			display_assertion(fname, lineno);
		else
			display_output("passed");
	}
}
