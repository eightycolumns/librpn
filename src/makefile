CFLAGS += -I ..

src_dir := ../$(src_dir)
test_dir := ../$(test_dir)
build_dir := ../$(build_dir)

.PHONY: all
all: $(build_dir)/$(lib_filename)

objects = $(patsubst %.c,%.o,$(wildcard $(src_dir)/*.c))

$(build_dir)/$(lib_filename): $(objects) | $(build_dir)
	ar rcs $@ $^

$(objects): %.o: %.h

$(build_dir):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(objects) $(build_dir)
