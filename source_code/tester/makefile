CC = g++

CFLAGS = -std=c++0x -fPIC -O -g

TARGET = ../../os/linux/comp/statlibs/libtester.a

OBJ_DIR = obj

INC_DIR = include

SRC_DIR = src

COMM_INC_DIR = ../communications/$(INC_DIR)
UTIL_INC_DIR = ../utilities/$(INC_DIR)
INTERFACE_INC_DIR = ../interfaces
VELODYNE_INC_DIR = ../products/velodyne/icd/$(INC_DIR)
VELODYNE_WRAPPER_INC_DIR = ../products/velodyne/wrapper/$(INC_DIR)
NOVATEL_INC_DIR = ../products/novatel/icd/$(INC_DIR)
NOVATEL_WRAPPER_INC_DIR = ../products/novatel/wrapper/$(INC_DIR)
TILTAN_INC_DIR = ../products/tiltan/icd/$(INC_DIR)
TILTAN_WRAPPER_INC_DIR = ../products/tiltan/wrapper/$(INC_DIR)
IDAN_INC_DIR = ../products/idan/icd/$(INC_DIR)
IDAN_WRAPPER_INC_DIR = ../products/idan/wrapper/$(INC_DIR)

INCLUDES = -I$(INC_DIR) \
			-I$(COMM_INC_DIR) \
			-I$(UTIL_INC_DIR) \
			-I$(INTERFACE_INC_DIR) \
			-I$(VELODYNE_INC_DIR) \
			-I$(VELODYNE_WRAPPER_INC_DIR) \
			-I$(NOVATEL_INC_DIR) \
			-I$(NOVATEL_WRAPPER_INC_DIR) \
			-I$(TILTAN_INC_DIR) \
			-I$(TILTAN_WRAPPER_INC_DIR) \
			-I$(IDAN_INC_DIR) \
			-I$(IDAN_WRAPPER_INC_DIR)
# take all h files on include dir
DEPS = $(wildcard $(INC_DIR)/*.h) \
		$(wildcard $(COMM_INC_DIR)/*.h) \
		$(wildcard $(UTIL_INC_DIR)/*.h) \
		$(wildcard $(INTERFACE_INC_DIR)/*.h) \
		$(wildcard $(VELODYNE_INC_DIR)/*.h) \
		$(wildcard $(VELODYNE_WRAPPER_INC_DIR)/*.h) \
		$(wildcard $(NOVATEL_INC_DIR)/*.h) \
		$(wildcard $(NOVATEL_WRAPPER_INC_DIR)/*.h) \
		$(wildcard $(TILTAN_INC_DIR)/*.h) \
		$(wildcard $(TILTAN_WRAPPER_INC_DIR)/*.h) \
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
