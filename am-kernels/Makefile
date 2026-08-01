clean:
	echo "Cleaning all sub-projects within depth 2"

### Clean all sub-projects within depth 2 (and ignore errors)
CLEAN_ALL = $(filter-out ./kernels/memu/,$(dir $(shell find . -mindepth 2 -name Makefile)))
clean-all: $(CLEAN_ALL) clean
$(CLEAN_ALL):
	-@$(MAKE) --no-print-directory -C $@ clean
.PHONY: clean-all $(CLEAN_ALL)
