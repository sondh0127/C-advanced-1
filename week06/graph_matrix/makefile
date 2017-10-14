TARGETS=${patsubst %.c,%,${wildcard ./main.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< graph_matrix.c

clean:
	rm -f ${TARGETS}