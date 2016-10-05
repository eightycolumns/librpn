MAKEFLAGS += -s

export CC = gcc
export CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -O2

export lib_name = rpn

export lib_header = $(lib_name).h
export lib_filename = lib$(lib_name).a
export lib_test_exe = $(lib_name)-test

export src_dir = src
export test_dir = test
export build_dir = build

dirs = $(src_dir) $(test_dir)

make_dirs = $(dirs:%=make-%)

.PHONY: all
all: $(make_dirs)

.PHONY: $(make_dirs)
$(make_dirs):
	$(MAKE) -C $(@:make-%=%)

.PHONY: check
check:
	./$(build_dir)/$(lib_test_exe)

clean_dirs = $(dirs:%=clean-%)

.PHONY: clean
clean: $(clean_dirs)

.PHONY: $(clean_dirs)
$(clean_dirs):
	$(MAKE) -C $(@:clean-%=%) clean
