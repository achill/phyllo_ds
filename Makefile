CC=gcc
CFLAGS=-O -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

phyllo_ds: phyllo_ds.o
	$(CC) -o phyllo_ds phyllo_ds.o $(CFLAGS)
