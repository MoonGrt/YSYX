include common.mk

_default:
	@echo "Please run 'make' under subprojects."
.PHONY: _default

clean-all: 
	$(MAKE) -C $(MEMU_HOME) clean-all
	$(MAKE) -C $(AM_HOME) clean-all
	$(MAKE) -C $(AM_TEST_HOME) clean-all
.PHONY: clean-all
