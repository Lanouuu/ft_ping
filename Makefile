NAME			=	ft_ping

CFLAGS			=	-Wall -Wextra -Werror -I ${INCLD_DIR} -g

CC				=	cc

GREEN			=	\033[0;32m

YELLOW			=	\033[0;33m

COLOUR_END		=	\033[0m

# **************************************************************************** #
#                                                                              #
#                                  SOURCES                                     #
#                                                                              #
# **************************************************************************** #

SOURCES_PATH	=	srcs/

SOURCES			= 	main.c \
					help.c \
					errors.c \
					init_data.c \
					parser.c \
					resolve.c \
					socket.c \
					packet.c \
					checksum.c \
					send.c \
					receive.c \
					analyze.c \
					display.c \
					statistics.c \
					signal.c \

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
	@${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	@printf "${GREEN}\33[2K\n${NAME} compiled\n${COLOUR_END}"

${OBJECTS_PATH}%.o:	${SOURCES_PATH}%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c $< -o $@ && printf "\33[2K\r${YELLOW}Compiling ${NAME} :${COLOUR_END} $@"

clean:
	@rm -rf ${OBJECTS_PATH}

fclean:
	@rm -rf ${OBJECTS_PATH}
	@rm -f ${NAME}
	@printf "${GREEN}${NAME} cleaned\n${COLOUR_END}"

re: fclean all

.PHONY: fclean clean all re bonus