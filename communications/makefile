CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../comp/statlibs/libcommunications.a

MKDIR = mkdir -p

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

UTIL_INC_DIR = ../utilities/$(INC_DIR)

INCLUDES = -I$(INC_DIR) \
			-I$(UTIL_INC_DIR)

# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) \
		$(wildcard $(UTIL_INC_DIR)/*.h) 
		
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJ = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

directories: $(OBJ_DIR)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(TARGET): $(OBJ)
	ar rcs $@ $^

.PHONY: all clean

clean:
	$(RM) $(OBJ_DIR)/*.o *~ core
