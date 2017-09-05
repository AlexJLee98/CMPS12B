CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = bubbleSort.o insertionSort.o mergeSort.o minSort.o quickSort.o sorting.o

.PHONY: all
all: sorting

sorting: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o sorting

bubbleSort.o: bubbleSort.c
	$(CC) $(CFLAGS) -c bubbleSort.c

insertionSort.o: insertionSort.c
	$(CC) $(CFLAGS) -c insertionSort.c

mergeSort.o: mergeSort.c
	$(CC) $(CFLAGS) -c mergeSort.c

minSort.o: minSort.c
	$(CC) $(CFLAGS) -c minSort.c

quickSort.o: quickSort.c
	$(CC) $(CFLAGS) -c quickSort.c

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) bubbleSort insertionSort mergeSort minSort quickSort sorting


