CC = gcc

CFLAGS = -g \
          -Iinclude

LDFLAGS = -L. \
          -Wl,-rpath,'$$ORIGIN'

LDLIBS = -lagisort

TARGET = agisort
SRCS = src/main.c

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

build:
	$(MAKE) -f makefile.build

build-run:
	$(MAKE) -f makefile.build
	./$(TARGET)
