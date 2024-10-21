GENERATES = esub
TRASH = *.o *~ o.* tmp_file1 tmp_file2

esub: esub.c
	cc $< -o $@ 

test: esub test1 test2

test1:
	echo "Mon 23 Oct 2023 12:25:18 PM MSK" | sed -E "s/(([[:digit:]]+).*)([[:digit:]]+)/<1=\1><2=\2><3=\3>/" >tmp_file1
	./esub "(([[:digit:]]+).*)([[:digit:]]+)" "<1=\1><2=\2><3=\3>" "Mon 23 Oct 2023 12:25:18 PM MSK" >tmp_file2
	cmp tmp_file1 tmp_file2
	@echo Test1: OK

STRING:="one two three"
SUBS:="\1 is actually 2"
REGEXP:="(two)"

test2:
	echo $(STRING) | sed -E "s/"$(REGEXP)"/"$(SUBS)"/" >tmp_file1
	./esub $(REGEXP) $(SUBS) $(STRING) >tmp_file2
	cmp tmp_file1 tmp_file2
	@echo Test2: OK

clean:
	rm -f $(TRASH) $(GENERATES)
