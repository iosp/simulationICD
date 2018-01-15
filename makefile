CC = g++

LDFLAGS = -shared

TARGET = comp/libvlp.so

LIBS = -lboost_system -lboost_thread

STAT_DIR = comp/statlibs

STAT_LIBS = $(STAT_DIR)/libvlpwrapper.a $(STAT_DIR)/libvelicd.a $(STAT_DIR)/libutils.a

INC_DIR_NAME = include
OBJ_DIR = obj

INC_ICD = products/velodyne/icd/$(INC_DIR_NAME)
INC_WRAPPER = products/velodyne/wrapper/$(INC_DIR_NAME)
INC_UTILS = utilities/$(INC_DIR_NAME)

INC_FILES = $(wildcard $(INC_ICD)/*.h) $(wildcard $(INC_WRAPPER)/*.h) $(wildcard $(INC_UTILS)/*.h)
# Change suffix to .o
_OBJ = $(addsuffix .o,$(basename $(INC_FILES)))
# Change suffix directory to obj
OBJ = ${subst $(INC_DIR_NAME),$(OBJ_DIR),$(_OBJ)}

SUBDIRS = utilities products

all: createdirs compdirs $(TARGET)

# create required directories
createdirs:
	mkdir -p comp
	mkdir -p comp/statlibs

# compile all sub directories
compdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

.PHONY: all clean

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(STAT_LIB)/*.a $(TARGET)
