CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../../../comp/statlibs/libvlpwrapper.a

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

VLP_INC_DIR = ../icd/$(INC_DIR)

INTERFACE_INC_DIR = ../../../interfaces

INCLUDES = -I$(INC_DIR) -I$(VLP_INC_DIR) -I$(INTERFACE_INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) $(wildcard $(VLP_INC_DIR)/*.h) $(wildcard $(INTERFACE_INC_DIR)/*.h)
# replace the name of all h files to the same name with o suffix
OBJ = $(DEPS:$(INC_DIR)/%.h=$(OBJ_DIR)/%.o)

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
