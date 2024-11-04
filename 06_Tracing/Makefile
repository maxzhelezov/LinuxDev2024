TRASH = *.o *~ o.* infile in_reference outfile out_reference infilePROTECT
TARGET = move
GENERATES = $(TARGET) protect.so
CFLAGS= -Wall -Wextra -O0 -g

define CREATE_FILES
	cal > infile
	cp infile in_reference
	echo "test" > outfile
	cp outfile out_reference
endef

define COMPARE_FILES_UNTAPERED
	cmp infile in_reference
	cmp outfile out_reference
endef


all: $(TARGET) protect.so

protect.so: protect.c
	gcc -shared -D_GNU_SOURCE -o protect.so protect.c

$(TARGET): $(TARGET).c
	cc $(CFLAGS) $< -o $@ 


test: move test1 test2 test3 test4 test5  test6

test1:
	$(CREATE_FILES)
	./move infile outfile || [ $$? = 0 ]
	[ ! -f infile ]
	[ -f outfile ]
	cmp in_reference outfile
	@echo $@: OK

test2:
	$(CREATE_FILES)
	strace -P infile -e fault=openat:when=1 ./move infile outfile || [ $$? = 2 ]
	$(COMPARE_FILES_UNTAPERED)
	@echo $@: OK

test3:
	$(CREATE_FILES)
	strace -P infile -e fault=read:when=1 ./move infile outfile || [ $$? = 5 ]
	$(COMPARE_FILES_UNTAPERED)
	@echo $@: OK

test4:
	$(CREATE_FILES)
	strace -P infile -e fault=close:when=1 ./move infile outfile || [ $$? = 8 ]
	$(COMPARE_FILES_UNTAPERED)
	@echo $@: OK

test5:
	$(CREATE_FILES)
	strace -P infile -e fault=unlink:when=1 ./move infile outfile || [ $$? = 9 ]
	# just failed to delete infile in the end 
	cmp infile in_reference
	cmp in_reference outfile
	@echo $@: OK

test6:
	cal > infilePROTECT
	cp infilePROTECT in_reference
	echo "test" > outfile
	cp outfile out_reference
	LD_PRELOAD=./protect.so ./move infilePROTECT outfile || [ $$? = 9 ]
	[ -f infilePROTECT ]
	cmp infilePROTECT in_reference
	cmp outfile in_reference
	@echo $@: OK





clean:
	rm -f $(TRASH) $(GENERATES)
