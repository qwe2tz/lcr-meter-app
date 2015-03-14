#Red Pitaya LCR meter Makefile

CC=$(CROSS_COMPILER)gcc
RM=rm

OBJECTS = main.o fpga_lcr.o worker.o lcr_algorithm.o
INCLUDE = #Nothing included yet.
CFLAGS  = -g -std=gnu99 -Wall -Werror $(INCLUDE)
LDFLAGS = -shared

OUT_DIR = ../
TARGET  = controller.so

all: clean $(TARGET)

clean: clean_c_app

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean_c_app:
	$(RM) -f $(C_OUT_NAME) $(OBJECTS) 
