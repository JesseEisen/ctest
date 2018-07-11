ctest:
	gcc ctest.c -o ctest -ldl

util:
	gcc -fPIC -shared util.c -o libutil.so

.PHONY:clean
clean:
	rm -rf ctest libutil.so
