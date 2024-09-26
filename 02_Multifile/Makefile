GENERATES = prog README prog-a liboutput.so prog-so
TRASH = *.o *~ o.* liboutput_static.a file1 file2 file3

define MOD_CMP
	sed -i "s/prog-a/prog/1" file2 
	sed -i "s/prog-so/prog/1" file3 
	cmp file1 file2
	cmp file2 file3
endef 

%.o:    %.c
	cc -fPIC $< -c -o $@

all: README prog prog-a prog-so

test: prog prog-a prog-so
	./prog 2>file1
	./prog-a 2>file2
	LD_LIBRARY_PATH="./" ./prog-so 2>file3
	$(MOD_CMP)
	@echo TEST 1: Ok
	
	./prog 123 >file1
	./prog-a 123 >file2
	LD_LIBRARY_PATH="./" ./prog-so 123 >file3
	$(MOD_CMP)
	@echo TEST 2: Ok
	
	./prog 1 2 3 >file1
	./prog-a 1 2 3 >file2
	LD_LIBRARY_PATH="./" ./prog-so 1 2 3 >file3
	$(MOD_CMP)
	@echo TEST 3: Ok


prog-so: prog.o liboutput.so
	cc prog.o -L. -loutput -o $@

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog-a: liboutput_static.a prog.o
	cc prog.o -L. -loutput_static -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

prog:   const.o fun.o prog.o
	cc $^ -o $@

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
