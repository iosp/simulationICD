MAKE = make -f

MAKEFILES = makefile_velodyne \
			makefile_novatel \
			makefile_tiltan \
			makefile_idan

all: compprods

# compile all sub directories
compprods:
	for makefile in $(MAKEFILES); do \
		$(MAKE) $$makefile; \
	done

.PHONY: all clean

clean:
	for makefile in $(MAKEFILES); do \
		$(MAKE) $$makefile clean; \
	done
