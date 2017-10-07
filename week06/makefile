TARGETS=${patsubst %.c,%,${wildcard ./graph_jrb.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< ../lib/Libfdr/jval.o ../lib/Libfdr/jrb.o

clean:
	rm -f ${TARGETS}