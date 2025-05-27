build:
	gcc main.c task1lib.c task2lib.c task3lib.c task4lib3.c -o a.out
run:
	./checker-linux-amd64 -i
clean:
	rm -rf a.out