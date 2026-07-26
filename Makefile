include common.mk

_default:
	@echo "Please run 'make' under subprojects."
.PHONY: _default

# Remove every generated file owned by the main workspace.  Source trees,
# patches and submodule working-tree changes are deliberately preserved.
clean-all:
	$(MAKE) -C $(MEMU_HOME) clean-all
	$(RM) -r $(MEMU_HOME)/out \
	         $(MEMU_HOME)/.mill \
	         $(MEMU_HOME)/.bsp \
	         $(MEMU_HOME)/.metals
	find $(MEMU_HOME)/tools -path $(MEMU_HOME)/tools/fixdep -prune -o \
	       -type d -name build -prune -exec $(RM) -r {} +
	$(RM) -r $(MEMU_HOME)/thirdpartys/OpenNoC/rtl \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/out \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/.mill \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/.bsp \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/.bloop \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/.metals \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/target \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/project/target \
	         $(MEMU_HOME)/thirdpartys/OpenNoC/project/project/target
	$(MAKE) -C $(AM_HOME) clean-all
	$(MAKE) -C $(AM_TEST_HOME) clean-all
	find $(AM_HOME) -type d -name build -prune -exec $(RM) -r {} +
	find $(AM_TEST_HOME) -type d -name build -prune -exec $(RM) -r {} +
	$(MAKE) -C thirdpartys/fceux-am clean
	$(RM) -r thirdpartys/rt-thread-am/bsp/abstract-machine/build
	$(RM) -r .metals .bsp .mill
	find $(MEMU_HOME) $(AM_HOME) $(AM_TEST_HOME) thirdpartys \
	       -type d -name .git -prune -o \
	       -type d \( -name .metals -o -name .bsp -o -name .mill \
	                  -o -name __pycache__ \) \
	       -prune -exec $(RM) -r {} +
	@echo "All workspace build artifacts have been removed."
.PHONY: clean-all
