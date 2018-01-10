CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../comp/statlibs/libutils.a

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

INCLUDES = -I$(INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h)
# replace the name of all h files to the same name with o suffix
OBJ = $(DEPS:$(INC_DIR)/%.h=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(TARGET): $(OBJ)
	ar rcs $@ $^

.PHONY: all clean

clean:
	$(RM) $(OBJ_DIR)/*.o *~ core
