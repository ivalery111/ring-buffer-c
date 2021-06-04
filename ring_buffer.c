#include "ring_buffer.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline size_t min(size_t x, size_t y) { return (x < y) ? x : y; }

int32_t rb_init(rb_t *rb, size_t buffer_size) {
  assert(rb != NULL);

  int32_t rc = RB_OK;

  rb->buffer = calloc(1, buffer_size);
  assert(rb->buffer != NULL);
  if (rb->buffer == NULL) {
    rc = RB_NOMEM;
    goto exit;
  }

  rb->buffer_size = buffer_size;
  rb->write = 0;
  rb->read = 0;
  rb->bytes_available = 0;

exit:
  return rc;
}

int32_t rb_put(rb_t *rb, const uint8_t *data, size_t data_size) {
  assert(rb != NULL);
  assert(data != NULL);

  int32_t rc = RB_OK;

  if (rb == NULL || data == NULL) {
    rc = RB_INVLID;
    goto exit;
  }

  const size_t part_1 = min(rb->buffer_size - rb->write, data_size);
  const size_t part_2 = data_size - part_1;

  memcpy(rb->buffer + rb->write, data, part_1);
  memcpy(rb->buffer, data + part_1, part_2);

  rb->write = (rb->write + data_size) % rb->buffer_size;

  rb->bytes_available += data_size;

exit:
  return rc;
}

int32_t rb_get(rb_t *rb, uint8_t *data, size_t data_size) {
  assert(rb != NULL);
  assert(data != NULL);

  int32_t rc = RB_OK;

  if (rb == NULL || data == NULL) {
    rc = RB_INVLID;
    goto exit;
  }

  const size_t part_1 = min(rb->buffer_size - rb->read, data_size);
  const size_t part_2 = data_size - part_1;

  memcpy(data, rb->buffer + rb->read, part_1);
  memcpy(data + part_1, rb->buffer, part_2);

  rb->read = (rb->read + data_size) % data_size;
  rb->bytes_available -= data_size;

exit:
  return rc;
}
