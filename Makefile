ctest:
	gcc ctest.c -o ctest -ldl

.PHONY:clean
clean:
	rm -rf ctest
