################################################################################
#                              CONFIGURATION                                   #
################################################################################

NAME			= MiniRT
#NAME_BONUS		= BonusRT

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
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

SRCS = $(SRCDIR)/main/main.c 				\
	   $(SRCDIR)/parser/parser.c			\
	   $(SRCDIR)/parser/parser_map.c		\
	   $(SRCDIR)/utils/utils.c				\
	   $(SRCDIR)/parser/parse_camera.c		\
	   $(SRCDIR)/parser/parse_ambient.c		\
	   $(SRCDIR)/parser/parse_light.c		\
	   $(SRCDIR)/parser/parse_plane.c		\
	   $(SRCDIR)/parser/parse_sphere.c		\
	   $(SRCDIR)/utils/utils2.c				\
	   $(SRCDIR)/parser/parse_cylinder.c	\
	   $(SRCDIR)/utils/utils3.c				\
	   $(SRCDIR)/finish/free_all.c			\
	   $(SRCDIR)/mlx/run_mlx.c				\
	   $(SRCDIR)/mlx/mlx_init.c				\
	   $(SRCDIR)/parser/parse_cone.c		\
	   $(SRCDIR)/parser/parse_bonus.c		\
	   $(SRCDIR)/mlx/render_scene.c			\
	   $(SRCDIR)/vec_op/vec_op1.c			\
	   $(SRCDIR)/vec_op/vec_op2.c




#SRCS_BONUS = \

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

$(NAME): Makefile $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX) $(LDFLAGS) -o $@
	@echo "\033[1;33mMiniRT\033[0m"

#$(NAME_BONUS): Makefile $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) $(LDFLAGS) -o $@
#	@echo "\033[1;33mMiniRT BonuS\033[0m"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

lib:
	@make -C $(LIBFT_DIR) --silent

dir:
	@mkdir -p $(OBJDIR) $(DEPDIR)

mlx:
	@cmake -S $(MLXDIR) -B $(MLXDIR)/build > /dev/null 2>&1
	@cmake --build $(MLXDIR)/build > /dev/null 2>&1

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJDIR) $(DEPDIR)
	@echo "\033[1;33mCHAU\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -rf $(MLXDIR)/build

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re dir bonus
