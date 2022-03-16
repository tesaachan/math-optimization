HEADER =	lab02.hpp

LIST =		lab02.cpp\
			midpoint_method.cpp\
			secant_method.cpp\
			newton_raphson_method.cpp\

EXEC =		lab02

MAKEFILE =	Makefile

OBJ = 		$(LIST:.cpp=.o)

FLAGS = 	-Wall -Wextra -Werror

%.o : 		%.cpp $(HEADER) $(MAKEFILE)
				g++ $(FLAGS) -c $< -o $@

$(EXEC) :	$(OBJ)
			g++ $(OBJ) -o $(EXEC)

clean : 	
			@rm -f $(OBJ) $(EXEC)
