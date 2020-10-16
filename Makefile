SRC_DIR = src
INS_DIR = install
TST_DIR = tests

CPPFLAGS= -I ${SRC_DIR} -I ${INS_DIR} -I ${TST_DIR}
CFLAGS= -std=c99 -Wall -Wextra

all: build code install report

bitboard.o: ${SRC_DIR}/bitboard.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -c

tools.o: ${SRC_DIR}/tools.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -c

tests.o: ${TST_DIR}/tests.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -c

minmax.o: bitboard.o ${SRC_DIR}/minmax.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -c

simple_strat.o: bitboard.o ${SRC_DIR}/simple_strat.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -c

test-bitboard: bitboard.o tests.o ${TST_DIR}/test_bitboard.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -o $@

test-tools: tools.o tests.o ${TST_DIR}/test_tools.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -o $@

test-minmax: bitboard.o minmax.o simple_strat.o ${TST_DIR}/test_minmax.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -o $@;./test-minmax

test-simple-strat: bitboard.o simple_strat.o ${TST_DIR}/test_simple_strat.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -o $@


build: ${SRC_DIR}/simple_strat.c ${SRC_DIR}/minmax.c ${SRC_DIR}/simple_player.c ${SRC_DIR}/player_minmax.c ${SRC_DIR}/player.c ${SRC_DIR}/bitboard.c
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -shared ${SRC_DIR}/player.c ${SRC_DIR}/bitboard.c -o ./P1_random.so
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -shared ${SRC_DIR}/minmax.c ${SRC_DIR}/player_minmax.c ${SRC_DIR}/bitboard.c -o ./P3_minmax.so
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -shared ${SRC_DIR}/simple_strat.c ${SRC_DIR}/bitboard.c ${SRC_DIR}/simple_player.c -o ./P2_simple.so

code: bitboard.o tools.o ${SRC_DIR}/project.c
	gcc ${CPPFLAGS} ${CFLAGS} $^ -o ./server -ldl

test: test-bitboard test-tools test-simple-strat
	./test-bitboard
	./test-tools
	./test-simple-strat

install: ./P1_random.so ./P2_simple.so ./P3_minmax.so ./server
	cp -f $^ ${INS_DIR}

clean:
	rm -f ${INS_DIR}/server ${INS_DIR}/*.so ./server *.so *.out *.o test-bitboard test-tools test-minmax test-simple-strat


