CPU_DIR = ./cpu

GPU_DIR = ./gpu

all: $(NAME)

$(NAME):
	@echo "--Compiling libft library--"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	@echo "--Compiling cuda-----------"
	@nvcc -c $(SRC_CUDA) -dc -Wno-deprecated-gpu-targets
	@echo "--Compiling sources--------"
	@gcc -c $(SRC)
	@mkdir -p bin
	@echo "--Creating executable------"
	@nvcc -o bin/$(NAME) $(OBJ) $(OBJ_CUDA) $(LIBFT) -Xlinker -framework,SDL2 \
	-gencode arch=compute_30,code=compute_30 \
    -gencode arch=compute_35,code=compute_35
	@echo "--Done---------------------"

clean:
	@echo "--Cleaning libraries-------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	@echo "--Cleaning output files----"
	@$(RM) $(OBJ)

fclean: clean
	@echo "--Cleaning executale------"
	@$(RM) $(NAME)

re: fclean all