include $(APEX)/$(OS).inc

TARGET = libap.a
SRCS = $(wildcard *.c)
OBJ = ${SRCS:.c=.o}
CFLAGS += -I../internal

.PHONY: all clean

all: $(TARGET) clean

%.o: %.c
	$(CC) $(CFLAGS) -c $(SRCS)

$(TARGET): $(OBJ)
	ar rcs ${APEXLIB}/$@ $^

clean:
	rm -f $(OBJ)
