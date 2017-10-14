TARGETS=${patsubst %.c,%,${wildcard ./main.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< bfs.c graph_jrb.c ../../lib/Libfdr/jval.o ../../lib/Libfdr/jrb.o ../../lib/Libfdr/dllist.o

clean:
	rm -f ${TARGETS}