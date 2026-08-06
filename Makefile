NAME			=	ft_ping

CFLAGS			=	-Wall -Wextra -Werror -I ${INCLD_DIR} -g

CC				=	cc

COLOUR_GREEN	=	\033[0;32m

COLOUR_END		=	\033[0m

# **************************************************************************** #
#                                                                              #
#                                  SOURCES                                     #
#                                                                              #
# **************************************************************************** #

SOURCES_PATH	=	srcs/

SOURCES	= 	main.c \
			parser.c \
			help.c \
			errors.c \
			init_data.c \

# **************************************************************************** #
#                                                                              #
#                                  OBJECTS                                     #
#                                                                              #
# **************************************************************************** #

OBJECTS_PATH	=	objs/

OBJECTS			=	$(addprefix ${OBJECTS_PATH}, ${SOURCES:.c=.o}) \

# **************************************************************************** #
#                                                                              #
#                                  INCLUDES                                    #
#                                                                              #
# **************************************************************************** #

INCLD_DIR		=	./includes/

INCLD			=	${INCLD_DIR}ft_ping.h

# **************************************************************************** #
#                                                                              #
#                                  RULES                                       #
#                                                                              #
# **************************************************************************** #

all: ${NAME}

${NAME}: ${OBJECTS} ${INCLD}
	@echo "Compilation - ${NAME}\n"
	@${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	@echo "${COLOUR_GREEN}${NAME} compiled\n${COLOUR_END}"

${OBJECTS_PATH}%.o:	${SOURCES_PATH}%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf ${OBJECTS_PATH}

fclean:
	@rm -rf ${OBJECTS_PATH}
	@rm -f ${NAME}
	@echo "${COLOUR_GREEN}${NAME} cleaned\n${COLOUR_END}"

re: fclean all

.PHONY: fclean clean all re bonus