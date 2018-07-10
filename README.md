## Ctest

This is a light autotest framwork for c.

## Usage

For Now, You can use it to test a simple c programming. it can not use in a huge project. And it can use to test a part of code.


For Example, my little project [cregex](https://github.com/JesseEisen/cregex). And i can write this test file named: `Test_re.c`

Notice, All the test files need to begin with `Test_` and all the test functions need to begin with `Test_` too.

Here is the test code:(The assert macro and result analyst will add later)

```c
#include "cregex.h"
#include <assert.h>
#include <stdio.h>

#define str "[a-zA-Z, ]*"

void 
Test_cregex_match(void)
{
	char *string  = "Hello, Today is 2017/11/27";
	char *pattern = "^" str "([0-9]{4})/([0-9]{2})/([0-9]{2})$";
	
	cregex_t  reg;
	cregex_init(&reg, 10);
	assert(cregex_match(&reg, pattern, string) != -1);
	cregex_free(&reg);
	printf("pass\n");
}

void
Test_cregex_match_all(void)
{
    char *string2  = "paranormal";
    char *pattern2 = "(a.)";
 	
	cregex_t  reg;
	cregex_init(&reg, 10);
	assert(cregex_match_all(&reg,pattern2,string2) != -1);
	cregex_free(&reg);
	printf("pass\n");
}

```

and the files in the `src` are:

```bash
$ ls
cregex.c cregex.h Test_re.c
```

Now, you just use the `ctest` to run this test just like:

```bash
$ ctest Test_re.c cregex.c
pass
pass
```

Use `gcc ctest.c -o ctest -ldl` to generate the `ctest` binary.


