cxx = gcc
target = ray
sdl = $(shell sdl2-config --cflags --libs)
cxxFlags = -Wall -Wextra -g -o $(target) $(target).c -lm
all: $(target)
$(target):$(target).c 
	$(cxx) $(cxxFlags) $(sdl)

r:
	./$(target)
clean:
	rm -f $(target)

.PHONY: r clean 