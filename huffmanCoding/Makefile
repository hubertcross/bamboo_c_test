all: huff.exe

# $@ matches the target; $&lt; matches the first dependent
huff.exe: huff.o
	gcc -o huff.exe huff.o;

huff.o: huff.c
	#gcc -c $&lt;
	gcc -c huff.c;
     
clean:
	rm huff.o huff.exe
