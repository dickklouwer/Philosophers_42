
#= Vars =#

NAME := philo

SRCS := main.c parse_input.c libft.c philosophers.c

SRCSDIR := srcs

OBJDIR := obj

OBJ := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

CFLAGS := -Wall -Wextra -g

INCLUDES :=  -I includes 

#= COLORS =#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#= Targets =#

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Building philosophers ...$(RESET)"
	@$(CC) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)

$(OBJDIR)/%.o: $(addprefix $(SRCSDIR)/, %.c)
	@echo "$(GREEN)Building object files ...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning ...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME) $(OBJDIR)

re: fclean all