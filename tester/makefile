CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../comp/statlibs/libtester.a

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

COMM_INC_DIR = ../communications/$(INC_DIR)
UTIL_INC_DIR = ../utilities/$(INC_DIR)
INTERFACE_INC_DIR = ../interfaces
VEL_INC_DIR = ../products/velodyne/icd/$(INC_DIR)
VEL_WRAPPER_INC_DIR = ../products/velodyne/wrapper/$(INC_DIR)
DGPS_INC_DIR = ../products/dgps/icd/$(INC_DIR)
DGPS_WRAPPER_INC_DIR = ../products/dgps/wrapper/$(INC_DIR)
INS_INC_DIR = ../products/ins/icd/$(INC_DIR)
INS_WRAPPER_INC_DIR = ../products/ins/wrapper/$(INC_DIR)
IDAN_INC_DIR = ../products/idan/icd/$(INC_DIR)
IDAN_WRAPPER_INC_DIR = ../products/idan/wrapper/$(INC_DIR)

INCLUDES = -I$(INC_DIR) \
			-I$(COMM_INC_DIR) \
			-I$(UTIL_INC_DIR) \
			-I$(INTERFACE_INC_DIR) \
			-I$(VEL_INC_DIR) \
			-I$(VEL_WRAPPER_INC_DIR) \
			-I$(DGPS_INC_DIR) \
			-I$(DGPS_WRAPPER_INC_DIR) \
			-I$(INS_INC_DIR) \
			-I$(INS_WRAPPER_INC_DIR) \
			-I$(IDAN_INC_DIR) \
			-I$(IDAN_WRAPPER_INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) \
		$(wildcard $(COMM_INC_DIR)/*.h) \
		$(wildcard $(UTIL_INC_DIR)/*.h) \
		$(wildcard $(INTERFACE_INC_DIR)/*.h) \
		$(wildcard $(VEL_INC_DIR)/*.h) \
		$(wildcard $(VEL_WRAPPER_INC_DIR)/*.h) \
		$(wildcard $(DGPS_INC_DIR)/*.h) \
		$(wildcard $(DGPS_WRAPPER_INC_DIR)/*.h) \
		$(wildcard $(INS_INC_DIR)/*.h) \
		$(wildcard $(INS_WRAPPER_INC_DIR)/*.h) \
		$(wildcard $(IDAN_INC_DIR)/*.h) \
		$(wildcard $(IDAN_WRAPPER_INC_DIR)/*.h)

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
