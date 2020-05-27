# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henri <henri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/05 23:07:16 by henri             #+#    #+#              #
#    Updated: 2020/05/23 16:18:38 by henri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = replace
CPP = clang++ -Wall -Wextra -Werror
SRCS = main.cpp Sed.cpp
OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	@$(CPP) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(OBJS) -o $(NAME)

x: $(NAME)
	 @./$(NAME) File World 42

fclean:
	rm -f $(NAME)
	rm -f $(OBJS)

re: fclean $(NAME)

.PHONY: re fclean
