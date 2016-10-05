CFLAGS += -I ..

src_dir := ../$(src_dir)
test_dir := ../$(test_dir)
build_dir := ../$(build_dir)

.PHONY: all
all: $(build_dir)/$(lib_test_exe)

objects = $(patsubst %.c,%.o,$(wildcard $(test_dir)/*.c))

vpath $(lib_filename) $(build_dir)

CFLAGS += $(shell pkg-config --cflags check)

LDFLAGS = -L$(build_dir) $(shell pkg-config --libs-only-L check)
LDLIBS = -l$(lib_name) $(shell pkg-config --libs-only-l check)

$(build_dir)/$(lib_test_exe): $(objects) -l$(lib_name) | $(build_dir)
	$(CC) $(CFLAGS) $(objects) -o $@ $(LDFLAGS) $(LDLIBS)

headers = $(wildcard $(test_dir)/*.h) $(src_dir)/$(lib_header)

$(objects): $(headers)

$(build_dir):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(objects) $(build_dir)
