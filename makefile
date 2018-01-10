CC = g++

LDFLAGS = -shared

TARGET = comp/libvlp.so

LIBS = -lboost_system -lboost_thread

STAT_LIB = comp/statlibs

STAT_LIBS = $(STAT_LIB)/libvlpwrapper.a $(STAT_LIB)/libvelicd.a $(STAT_LIB)/libutils.a

D1 = products/velodyne/icd/obj
D2 = products/velodyne/wrapper/obj
D3 = utilities/obj

INC_DIR = include
OBJ_DIR = obj

# replace the name of all h files to the same name with o suffix
OBJ = $(D1)/VLPCommunication.o $(D1)/VLPCommunication16.o $(D1)/VLPCommunication32.o \
		$(D2)/VLPPluginAPI.o $(D2)/VLPCommunicationWrapper.o \
		$(D3)/Logger.o $(D3)/Utilities.o

DIRS = utilities products

all: createdirs makedirs $(TARGET)

createdirs:
	mkdir -p comp
	mkdir -p comp/statlibs

makedirs:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir; \
	done

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

.PHONY: all clean

clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(STAT_LIB)/*.a $(TARGET)
