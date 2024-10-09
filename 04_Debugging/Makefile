GENERATES = range
TRASH = *.o *~ o.* tmp_file 

range: range.c
	cc -g -O0 $< -o $@ 

test: test1 test2

test1:
	gdb -quiet -batch range -x script1.py | grep "@@@" | sed 's/@@@//1' >tmp_file
	cmp tmp_file test1_answer
	@echo Test1: OK

test2:
	gdb -quiet -batch range -x script2.py | grep "@@@" | sed 's/@@@//1' >tmp_file
	cmp tmp_file test2_answer
	@echo Test2: OK

clean:
	rm -f $(TRASH) $(GENERATES)
