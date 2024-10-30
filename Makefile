NAME		=	main

SRC			=	src/main.cpp

OBJ			=	$(SRC:.cpp=.o)

CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

LIBS		=	-lsfml-graphics -lsfml-window -lsfml-system

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.cpp
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

clean:
			${RM} $(OBJ)

fclean: 	clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
