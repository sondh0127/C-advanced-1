TARGETS=${patsubst %.c,%,${wildcard ./main.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< graph_jrb.c ../../lib/Libfdr/jval.o ../../lib/Libfdr/jrb.o

clean:
	rm -f ${TARGETS}