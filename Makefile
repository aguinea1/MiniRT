################################################################################
#                              CONFIGURATION                                   #
################################################################################

NAME			= MINI.RT
#NAME_BONUS		= BonusRT

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -Ofast -g #-fsanitize=address
THFLAGS			= -lpthread
DEPFLAGS		= -MMD -MF $(DEPDIR)/$*.d
LDFLAGS			= -lm

INCLUDE			= -Iinc -Ilibft -I/usr/include

SRCDIR			= mandatory/src
OBJDIR			= obj
DEPDIR			= deps
LIBFT_DIR		= libs/libft
INC_DIR			= mandatory/header
MLXDIR			= libs/MLX42
MLX				= $(MLXDIR)/build/libmlx42.a -ldl -lglfw -lm

################################################################################
#                              SOURCE FILES                                    #
################################################################################

SRCS = $(SRCDIR)/main/main.c 					\
	   $(SRCDIR)/parser/parser.c				\
	   $(SRCDIR)/parser/parser_map.c			\
	   $(SRCDIR)/utils/utils.c					\
	   $(SRCDIR)/parser/parse_camera.c			\
	   $(SRCDIR)/parser/parse_ambient.c			\
	   $(SRCDIR)/parser/parse_light.c			\
	   $(SRCDIR)/parser/parse_plane.c			\
	   $(SRCDIR)/parser/parse_sphere.c			\
	   $(SRCDIR)/utils/utils2.c					\
	   $(SRCDIR)/parser/parse_cylinder.c		\
	   $(SRCDIR)/utils/utils3.c					\
	   $(SRCDIR)/finish/free_all.c				\
	   $(SRCDIR)/mlx/run_mlx.c					\
	   $(SRCDIR)/mlx/mlx_init.c					\
	   $(SRCDIR)/parser/parse_cone.c			\
	   $(SRCDIR)/parser/parse_bonus.c			\
	   $(SRCDIR)/render/render_scene.c			\
	   $(SRCDIR)/vec_op/vec_op1.c				\
	   $(SRCDIR)/vec_op/vec_op2.c				\
	   $(SRCDIR)/render/utils_render_scene.c	\
	   $(SRCDIR)/threads/init_threads.c			\
	   $(SRCDIR)/render/hit_scene.c				\
	   $(SRCDIR)/render/hit_sphere.c			\
	   $(SRCDIR)/render/hit_plane.c				\
	   $(SRCDIR)/render/hit_cone.c				\
	   $(SRCDIR)/render/hit_cylinder.c			\
	   $(SRCDIR)/utils/utils4.c					\
	   $(SRCDIR)/render/setup_scene.c			\
	   $(SRCDIR)/vec_op/vec_op3.c				\
	   $(SRCDIR)/render/ray_backandmore.c		\
	   $(SRCDIR)/utils/utils_parser.c			\
	   $(SRCDIR)/utils/utils_cylinder.c


LIBFT_SRCS = \
	libs/libft/ft_isascii.c \
	libs/libft/ft_memcpy.c \
	libs/libft/ft_putstr_fd.c \
	libs/libft/ft_strlcat.c \
	libs/libft/ft_strrchr.c \
	libs/libft/ft_atoi.c \
	libs/libft/ft_isdigit.c \
	libs/libft/ft_memmove.c \
	libs/libft/ft_split.c \
	libs/libft/ft_strlcpy.c \
	libs/libft/ft_strtrim.c \
	libs/libft/ft_bzero.c \
	libs/libft/ft_isprint.c \
	libs/libft/ft_memset.c \
	libs/libft/ft_strchr.c \
	libs/libft/ft_strlen.c \
	libs/libft/ft_substr.c \
	libs/libft/ft_calloc.c \
	libs/libft/ft_itoa.c \
	libs/libft/ft_putchar_fd.c \
	libs/libft/ft_strdup.c \
	libs/libft/ft_strndup.c \
	libs/libft/ft_strmapi.c \
	libs/libft/ft_tolower.c \
	libs/libft/ft_isalnum.c \
	libs/libft/ft_memchr.c \
	libs/libft/ft_putendl_fd.c \
	libs/libft/ft_striteri.c \
	libs/libft/ft_strncmp.c \
	libs/libft/ft_toupper.c \
	libs/libft/ft_isalpha.c \
	libs/libft/ft_memcmp.c \
	libs/libft/ft_putnbr_fd.c \
	libs/libft/ft_strjoin.c \
	libs/libft/ft_strnstr.c \
	libs/libft/ft_free_array.c \
	libs/libft/ft_free_int_array.c \
	libs/libft/ft_strspn.c \
	libs/libft/ft_strcspn.c \
	libs/libft/ft_strcmp.c \
	libs/libft/ft_isspecial.c \
	libs/libft/ft_isspace.c \
	libs/libft/ft_strcpy.c \
	libs/libft/ft_strcat.c \
	libs/libft/ft_issigneddigit.c \
	libs/libft/ft_printf.c \
	libs/libft/type_cs.c \
	libs/libft/type_num.c \
	libs/libft/type_xXp.c \
	libs/libft/ft_realloc.c \
	libs/libft/ft_lstnew.c \
	libs/libft/ft_lstadd_front.c \
	libs/libft/ft_lstsize.c \
	libs/libft/ft_lstlast.c \
	libs/libft/ft_lstadd_back.c \
	libs/libft/ft_lstdelone.c \
	libs/libft/ft_lstclear.c \
	libs/libft/ft_lstiter.c \
	libs/libft/ft_lstmap.c \
	libs/libft/get_next_line.c


################################################################################
#                             OBJECTS & DEPS                                   #
################################################################################

OBJS			= $(SRCS:%.c=$(OBJDIR)/%.o)
#OBJS_BONUS		= $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)
DEPS			= $(OBJS:%.o=$(DEPDIR)/%.d)
#DEPS_BONUS		= $(OBJS_BONUS:%.o=$(DEPDIR)/%.d)

LIBFT_A			= $(LIBFT_DIR)/libft.a
HEADERS			= $(INC_DIR)/minirt.h
#HEADERS_BONUS	= inc/minishell_bonus.h libft/libft.h


################################################################################
#                              RULES                                           #
################################################################################

all: dir lib mlx $(NAME)

bonus: dir lib $(NAME_BONUS)

$(NAME): Makefile $(OBJS) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX) $(LDFLAGS) $(THFLAGS) -o $@
	@echo "\033[1;36m"
	@echo "           ╔══════════════════════════════════════╗"
	@echo "           ║          🌀  M I N I R T  🌀         ║"
	@echo "           ║                                      ║"
	@echo "           ║          lbellmas && aguinea         ║"
	@echo "           ╚══════════════════════════════════════╝"
	@echo "                                                           "
	@echo "          ███╗░░░███╗██╗███╗░░██╗██╗██╗██████╗░████████╗"
	@echo "          ████╗░████║██║████╗░██║██║██║██╔══██╗╚══██╔══╝"
	@echo "          ██╔████╔██║██║██╔██╗██║██║██║██████╔╝░░░██║░░░"
	@echo "          ██║╚██╔╝██║██║██║╚████║██║██║██╔══██╗░░░██║░░░"
	@echo "          ██║░╚═╝░██║██║██║░╚███║██║██║██║░░██║░░░██║░░░"
	@echo "          ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═╝╚═╝░░╚═╝░░░╚═╝░░░.🆁🆃"
	@echo "\033[0m"

#$(NAME_BONUS): Makefile $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) $(LDFLAGS) -o $@
#	@echo "\033[1;33mMiniRT BonuS\033[0m"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

lib:	$(LIBFT_A)

$(LIBFT_A):	$(LIBFT_SRCS)
	@make -C $(LIBFT_DIR) --silent

dir:
	@mkdir -p $(OBJDIR) $(DEPDIR)

MLX_DONE = $(MLXDIR)/build/libmlx42.a

mlx: $(MLX_DONE)

$(MLX_DONE):
	@cmake -S $(MLXDIR) -B $(MLXDIR)/build > /dev/null 2>&1
	@cmake --build $(MLXDIR)/build > /dev/null 2>&1

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJDIR) $(DEPDIR)
	@echo "\033[1;36m"
	@echo "            ░█████╗░██╗░░██╗░█████╗░██╗░░░██╗██╗░░░██╗"
	@echo "            ██╔══██╗██║░░██║██╔══██╗██║░░░██║██║░░░██║"
	@echo "            ██║░░╚═╝███████║███████║██║░░░██║██║░░░██║"
	@echo "            ██║░░██╗██╔══██║██╔══██║██║░░░██║██║░░░██║"
	@echo "            ╚█████╔╝██║░░██║██║░░██║╚██████╔╝╚██████╔╝"
	@echo "░            ╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚═════╝░░╚═════╝░.🆁🆃"
	@echo "\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -rf $(MLXDIR)/build

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re dir bonus
