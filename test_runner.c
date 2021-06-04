#include "ring_buffer.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {

  int32_t rc = (-1);

  rb_t rb;
  rc = rb_init(&rb, 64);
  assert(rc == RB_OK);

  rc = rb_put(&rb, "Hello ", strlen("Hello "));
  assert(rc == RB_OK);
  rc = rb_put(&rb, "Friend!\n", strlen("Friend!\n"));
  assert(rc == RB_OK);

  char buffer[6 + 9];

  rc = rb_get(&rb, buffer, (6 + 9));
  fprintf(stdout, "buffer: %s\n", buffer);

  fprintf(stdout, "Done!\n");

  return 0;
}
