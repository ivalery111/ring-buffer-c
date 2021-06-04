#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>

enum {
  RB_OK = 0,
  RB_NOMEM = (-1),
  RB_INVLID = (-2),
};

typedef struct {
  uint8_t *buffer;
  size_t buffer_size;
  size_t bytes_available; /* Bytes available for reading */

  size_t read;  /* Read position pointer */
  size_t write; /* Write position pointer */
} rb_t;

int32_t rb_init(rb_t *rb, size_t buffer_size);
int32_t rb_destroy(rb_t *rb);

int32_t rb_put(rb_t *rb, const uint8_t *data, size_t data_size);
int32_t rb_get(rb_t *rb, uint8_t *data, size_t data_size);

#endif
