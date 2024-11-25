TRASH = *.o *~ o.* 
TARGET = lab lab1 lab2 lab3
GENERATES = $(TARGET) lab1.c lab2.c lab3.c
CFLAGS= -Wall -Wextra -O0 -g
OFILES= lab.o lab1.o lab2.o lab3.o


all: $(TARGET)

run: $(TARGET)
	./lab
	./lab1 8
	./lab2 " @" 5
	./lab3 42 ".#" 6 

%.o: %.c
	cc $(CFLAGS) $< -c -o $@ 

$(TARGET): $(OFILES)
	cc $(CFLAGS) $@.o -o $@

lab1.c: lab.c
	patch lab.c 0001-Add-first-argument.patch -o lab1.c

lab2.c: lab1.c
	patch lab1.c -p2 0002-Add-custom-walls-and-passways.patch -o lab2.c

lab3.c: lab2.c
	patch lab2.c 0003-Add-seed-as-argument.patch -o lab3.c

clean:
	rm -f $(TRASH) $(GENERATES)
