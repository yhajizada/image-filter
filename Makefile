filter: main.c
	gcc -O2 main.c -o filter -lm

clean:
	rm -f filter output.jpg
