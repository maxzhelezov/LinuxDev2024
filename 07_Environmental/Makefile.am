CFLAGS= -Wall -Wextra -O0 -g
LDADD = $(LIBREADLINE)

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

TESTS = test1.sh test2.sh test3.sh test4.sh

test1.sh:
	set -f
	echo [ "`echo "SHA1 rhasher.c" | ./rhasher | sed "2q;d"`" = "`sha1sum rhasher.c |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ] > $@
	chmod +x $@

test2.sh:
	set -f
	echo [ "`echo "MD5 rhasher.c" | ./rhasher | sed "2q;d"`" = "`md5sum rhasher.c |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ] > $@
	chmod +x $@

test3.sh:
	set -f
	echo [ "`echo "MD5 \\"asd " | ./rhasher | sed "2q;d"`" = "` printf "\\"asd" | md5sum |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ] > $@
	chmod +x $@

test4.sh:
	echo ./configure --without-getline > $@
	echo make >> $@
	set -f
	echo [ "`echo "SHA1 rhasher.c" | ./rhasher | sed "2q;d"`" = "`sha1sum rhasher.c |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ] >> $@
	echo [ "`echo "MD5 rhasher.c" | ./rhasher | sed "2q;d"`" = "`md5sum rhasher.c |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ] >> $@
	echo [ "`echo "MD5 \\"asd " | ./rhasher | sed "2q;d"`" = "` printf "\\"asd" | md5sum |  tr "[:lower:]" "[:upper:]" | sed "s/ .*//"`" ]  >> $@
	chmod +x $@

gitclean:
	git clean -xdf
