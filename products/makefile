DIRS = velodyne

all:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir; \
	done

.PHONY: all clean

clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
