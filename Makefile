PROGNAME = gps_test
CC = gcc


CFLAGS = -o0 -ggdb3 ${CMP_OPTS}
###CFLAGS = -oS
LDFLAG =  -lgps

OBJS = gps_test.o utils.o
C_FILES = gps_test.c utils.o

TMPFILES =  *.c~ *.h~

all: ${PROGNAME}

${PROGNAME}: ${OBJS} Makefile
	${CC} -o ${PROGNAME} ${OBJS} ${LDFLAG}

clean:
	@rm -f $(subst /,\,${OBJS}) ${PROGNAME} *.*~

%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@


.PHONY : clean
