#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void *sbrk(intptr_t increment);
void *memset(void *ptr, int value, size_t num);

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFSIZ];
  ssize_t len = snprintf(buf, BUFSIZ, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  write(STDOUT_FILENO, buf, len);
}

void *increase_heap_size(int extra_size) {
  size_t numbytes = extra_size;
  void *allocated_ptr = sbrk((intptr_t)numbytes);
  return allocated_ptr;
}

int main(void) {
  void *start = increase_heap_size(256);
  struct header *block1 = (struct header *)start;

  struct header *block2 = (struct header *)(start + 128);

  block1->next = NULL;
  block1->size = 128;
  block2->size = 128;
  block2->next = block1;
  memset(block1 + 1, 0, 128 - sizeof(*block1));
  memset(block2 + 1, 0, 128 - sizeof(*block2));

  print_out("BLock 1 address: %p\n", &block1, sizeof(block1));
  print_out("BLock 2 address: %p\n", &block2, sizeof(block2));
  print_out("Block 1 Size: %d\n", &(block1->size), sizeof(block1->size));
  print_out("Block 2 Size: %d\n", &(block2->size), sizeof(block2->size));
  print_out("Block 1 Next: %p\n", &(block1->next), sizeof(block1->next));
  print_out("Block 2 Next: %p\n", &(block2->next), sizeof(block2->next));
}
