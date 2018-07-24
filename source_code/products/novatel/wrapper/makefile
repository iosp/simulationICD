CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../../../../os/linux/comp/statlibs/libnovatelwrapper.a

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

PROD_INC_DIR = ../icd/$(INC_DIR)

INTERFACE_INC_DIR = ../../../interfaces

INCLUDES = -I$(INC_DIR) \
			-I$(PROD_INC_DIR) \
			-I$(INTERFACE_INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) \
		$(wildcard $(PROD_INC_DIR)/*.h) \
		$(wildcard $(INTERFACE_INC_DIR)/*.h)

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJ = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

directories: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(TARGET): $(OBJ)
	ar rcs $@ $^

.PHONY: all clean

clean:
	$(RM) $(OBJ_DIR)/*.o *~ core
