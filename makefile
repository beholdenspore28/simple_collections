SRC            := *.c
INC            := -I.
C              := clang
OUT            := program.out

CFLAGS_DEBUG   := -g3 -fsanitize=address,undefined
CFLAGS_SMALL   := -Oz -flto
CFLAGS_RELEASE := -flto -O3 

CFLAGS         ?= -Wall            \
									-Wextra          \
									-Wpedantic       \
									-std=c99         \
									-ferror-limit=15 \
									${CFLAGS_DEBUG}

build:
	${C} ${SRC} ${CFLAGS} ${INC} -o ${OUT} 
	./${OUT}
