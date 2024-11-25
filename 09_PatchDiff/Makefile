TRASH = *.o *~ o.* 
TARGET = lab
GENERATES = $(TARGET)
CFLAGS= -Wall -Wextra -O0 -g

all: $(TARGET)

run: $(TARGET)
	./lab

$(TARGET): $(TARGET).c
	cc $(CFLAGS) $< -o $@ 

clean:
	rm -f $(TRASH) $(GENERATES)
