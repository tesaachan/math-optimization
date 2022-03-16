HEADER =	lab01.hpp

LIST =		lab01.cpp\
			enum_method.cpp\
			bitwise_method.cpp\
			bisection_method.cpp\
			dichot_method.cpp\
			golden_section_method.cpp\
			fibonacci_method.cpp\
			quad_interp_method.cpp\

EXEC =		lab01

MAKEFILE =	Makefile

OBJ = 		$(LIST:.cpp=.o)

FLAGS = 	-Wall -Wextra -Werror

%.o : 		%.cpp $(HEADER) $(MAKEFILE)
				g++ $(FLAGS) -c $< -o $@

$(EXEC) :	$(OBJ)
			g++ $(OBJ) -o $(EXEC)

clean : 	
			@rm -f $(OBJ) $(EXEC)
