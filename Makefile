##
## EPITECH PROJECT, 2026
## solostumper
## File description:
## Makefile
##
CC			=	epiclang
TEST_CC		=	clang

SRC_DIR 	=	./src
OBJ_DIR 	=	./obj
TEST_DIR		=	./tests
TEST_OBJ_DIR	=	./obj_tests
TEST_BIN		=	./tests_runner

INCLUDE		=	-I./include/
CLIBS		=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm
CFLAGS		=	-Wall -Wextra -W -g3 $(INCLUDE)
TEST_CFLAGS	=	-Wall -Wextra -W -g3 $(INCLUDE) --coverage
TEST_LDFLAGS	=	--coverage
GCOVR		=	gcovr
GCOV_EXEC	=	$(shell if command -v llvm-cov-20 >/dev/null 2>&1; then echo "llvm-cov-20 gcov"; elif command -v llvm-cov >/dev/null 2>&1; then echo "llvm-cov gcov"; else echo "gcov"; fi)

SRC			=	$(SRC_DIR)/main.c					\
				$(SRC_DIR)/my_inctype.c				\
				$(SRC_DIR)/my_strcmp.c				\
				$(SRC_DIR)/destroy_editor.c			\
				$(SRC_DIR)/save.c					\
				$(SRC_DIR)/size.c					\
				$(SRC_DIR)/handle_event.c			\
				$(SRC_DIR)/handle_render.c			\
				$(SRC_DIR)/destroy_world.c			\
				$(SRC_DIR)/init_editor.c			\
				$(SRC_DIR)/init_world.c				\
				$(SRC_DIR)/destroy_matrix.c			\
				$(SRC_DIR)/create_matrix.c			\
				$(SRC_DIR)/project_iso_point.c		\
				$(SRC_DIR)/camera_displacements.c	\
				$(SRC_DIR)/is_visible_on_screen.c	\
				$(SRC_DIR)/select.c 				\
				$(SRC_DIR)/zoom.c					\
				$(SRC_DIR)/render_vertexes.c		\
				$(SRC_DIR)/actualize_projection.c	\
				$(SRC_DIR)/palette_range.c			\

OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRC		=	$(TEST_DIR)/test_main.c				\
				$(SRC_DIR)/my_inctype.c				\
				$(SRC_DIR)/my_strcmp.c				\
				$(SRC_DIR)/size.c					\

TEST_OBJ		=	$(TEST_SRC:$(TEST_DIR)/%.c=$(TEST_OBJ_DIR)/tests/%.o)
TEST_OBJ		:=	$(TEST_OBJ:$(SRC_DIR)/%.c=$(TEST_OBJ_DIR)/src/%.o)

NAME		=	./my_world

MKDIRP		=	mkdir -p
RMRF		=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
	@echo "\n==== Creating Binary $@ ====\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	@echo "\tFINISHED"
	@echo "\n==== Creating Binary $@ ====\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "\n ~ Compiling : $< to $@..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\tDone"

$(OBJ_DIR):
	@echo "\n + Creating .o directory..."
	@$(MKDIRP) $(OBJ_DIR)
	@echo "\tDone"

$(TEST_OBJ_DIR):
	@echo "\n + Creating test .o directory..."
	@$(MKDIRP) $(TEST_OBJ_DIR)/tests
	@$(MKDIRP) $(TEST_OBJ_DIR)/src
	@echo "\tDone"

$(TEST_OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	@echo "\n ~ Compiling test: $< to $@..."
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@
	@echo "\tDone"

$(TEST_OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	@echo "\n ~ Compiling source for tests: $< to $@..."
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@
	@echo "\tDone"

$(TEST_BIN): $(TEST_OBJ)
	@echo "\n==== Creating test binary $@ ====\n"
	@$(TEST_CC) $(TEST_CFLAGS) -o $@ $^ $(TEST_LDFLAGS)
	@echo "\tFINISHED"

test-clean:
	@echo "\n - Deleting test artifacts..."
	@$(RMRF) $(TEST_OBJ_DIR) $(TEST_BIN)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@echo "\tDone"

test-run: test-clean $(TEST_BIN)
	@echo "\n==== Running unit tests ====\n"
	@$(TEST_BIN)
	@echo "\n==== Coverage report ====\n"
	@$(GCOVR) --root . --filter '^src/' --exclude '^tests/' --gcov-executable "$(GCOV_EXEC)"
clean:
	@echo "\n - Deleting .o directory..."
	@$(RMRF) $(OBJ_DIR)
	@echo "\tDone"

fclean:		clean
	@echo "\n==== Deleting Binary $(NAME) ====\n"
	@$(RMRF) $(NAME) $(TEST_BIN)
	@echo "\tFINISHED"
	@echo "\n==== Deleting Binary $(NAME) ====\n"

re:			fclean all

.PHONY:	all clean fclean re test-clean test-run