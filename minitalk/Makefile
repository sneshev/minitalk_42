# **************************************************************************** #
#                                  MAKEFILE                                    #
# **************************************************************************** #

# Project
NAME_SERVER = server
NAME_CLIENT = client

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Directories
OBJDIR  = obj
SRCS    = server.c client.c
OBJS    = $(SRCS:%.c=$(OBJDIR)/%.o)

# Libft
LIBFT_DIR = libft
LIBFT_A   = $(LIBFT_DIR)/libft.a

# Include libft headers if needed
INCLUDES = -I$(LIBFT_DIR)

# Default target
all: $(LIBFT_A) $(NAME_SERVER) $(NAME_CLIENT)

# Create object directory if not exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link server
$(NAME_SERVER): $(OBJDIR)/server.o $(LIBFT_A)
	$(CC) $(CFLAGS) $^ -o $@

# Link client
$(NAME_CLIENT): $(OBJDIR)/client.o $(LIBFT_A)
	$(CC) $(CFLAGS) $^ -o $@

# Build libft using its own Makefile
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# Clean project objects (not libft)
clean:
	rm -rf $(OBJDIR)

# Clean everything (including libft)
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re