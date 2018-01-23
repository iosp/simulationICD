CC = g++

LDFLAGS = -shared

TARGET_VLP = comp/libvlp.so

TARGET_DGPS = comp/libdgps.so

EX_LIBS = -lboost_system -lboost_thread

STAT_DIR = comp/statlibs

STAT_VEL_LIBS_BASE_NAMES = velicd \
							vlpwrapper \
							utils

STAT_DGPS_LIBS_BASE_NAMES = dgpsicd \
							dgpswrapper \
							utils

STAT_VEL_LIBS = $(addprefix -l, $(STAT_VEL_LIBS_BASE_NAMES))

STAT_DGPS_LIBS = $(addprefix -l, $(STAT_DGPS_LIBS_BASE_NAMES))

_STAT_VEL_LIB_DEPS = $(addprefix $(STAT_DIR)/lib, $(STAT_VEL_LIBS_BASE_NAMES))
STAT_VEL_LIB_DEPS = $(addsuffix .a, $(_STAT_VEL_LIB_DEPS))

_STAT_DGPS_LIB_DEPS = $(addprefix $(STAT_DIR)/lib, $(STAT_DGPS_LIBS_BASE_NAMES))
STAT_DGPS_LIB_DEPS = $(addsuffix .a, $(_STAT_DGPS_LIB_DEPS))

SUBDIRS = utilities products

all: createdirs compdirs $(TARGET_VLP) $(TARGET_DGPS)

# create required directories
createdirs:
	mkdir -p comp
	mkdir -p $(STAT_DIR)

# compile all sub directories
compdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

$(TARGET_VLP): $(STAT_VEL_LIB_DEPS)
	$(CC) $(LDFLAGS) -L$(STAT_DIR) -o $@ -Wl,-whole-archive $(STAT_VEL_LIBS) -Wl,-no-whole-archive $(EX_LIBS)

$(TARGET_DGPS):  $(STAT_DGPS_LIB_DEPS)
	$(CC) $(LDFLAGS) -L$(STAT_DIR) -o $@ -Wl,-whole-archive $(STAT_DGPS_LIBS) -Wl,-no-whole-archive $(EX_LIBS)

.PHONY: all clean

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(STAT_DIR)/*.a $(TARGET_VLP) $(TARGET_DGPS)
