.PHONY: all clean fclean re

NAME = philo

SRCS_FILES = main.c\
			 utils.c\

INCLUDES = include/philo.h

SRCS_DIR = src/
OBJS_DIR = .objects/

SRCS = $(addprefix ${SRCS_DIR},${SRCS_FILES})
OBJS = $(patsubst %.c, ${OBJS_DIR}%.o, ${SRCS})

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}
	@echo "${GREEN}${NAME} done!${END}"

${NAME}: ${OBJS} ${LIBFT} 
	cc ${CFLAGS} ${OBJS} -o ${NAME}  

${OBJS_DIR}%.o: %.c ${INCLUDES} Makefile
	mkdir -p $(shell dirname $@)
	cc ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS_DIR}
	@echo "${RED}$@ done!${END}"

fclean: clean
	rm -f ${NAME}
	@echo "${RED}$@ done!${END}"

re: fclean all

RED = \033[1;31m
GREEN = \033[1;32m
END = \033[0m
