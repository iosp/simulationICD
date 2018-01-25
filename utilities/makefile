CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../comp/statlibs/libutils.a

MKDIR = mkdir -p

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

INTERFACE_INC_DIR = ../interfaces

INCLUDES = -I$(INC_DIR) \
			-I$(INTERFACE_INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) \
		$(wildcard $(INTERFACE_INC_DIR)/*.h)

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# replace the name of all cpp files to the same name with o suffix
OBJ = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

directories:
	$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(TARGET): $(OBJ)
	ar rcs $@ $^

.PHONY: all clean

clean:
	$(RM) $(OBJ_DIR)/*.o *~ core
