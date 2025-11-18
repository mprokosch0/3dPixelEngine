NAME = 3dPixelEngine

CXX = c++

CPPFLAGS = -Wextra -Werror -Iincludes -O3 -g

LDFLAGS = -lglfw  -lGL -lm

SRCS = 	srcs/main.cpp srcs/Opengl.cpp srcs/Render.cpp srcs/Shaders.cpp srcs/ShadersUtils.cpp \
		srcs/Mesh.cpp srcs/Entity.cpp srcs/Menu.cpp srcs/Shapes.cpp\

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
WHITE = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	@echo "$(BLUE)Removing objects files ..."
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Removing Complete !$(WHITE)"

fclean: clean
	@echo "$(YELLOW)Removing archives and executables ..."
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(YELLOW)Removing Complete !$(WHITE)"

re: fclean all

.PHONY: all clean fclean re