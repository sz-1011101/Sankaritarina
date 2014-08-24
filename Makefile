CPP_FILES := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf
CC_FLAGS := -std=c++11
OBJ_NAME := sankaritarina_runable

sankaritarina: $(OBJS)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<
