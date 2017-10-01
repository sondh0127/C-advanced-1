TARGETS=${patsubst %.c,%,${wildcard ./*.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< -Lbt/lib -lbt -Ibt/inc

clean:
	rm -f ${TARGETS}