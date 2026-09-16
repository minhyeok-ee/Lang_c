#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#include <stdint.h>

uint32_t set_bit(uint32_t value, int n);
uint32_t clear_bit(uint32_t value, int n);
uint32_t toggle_bit(uint32_t value, int n);
int is_bit_set(uint32_t value, int n);
int count_ones(uint32_t value);
int is_power_of_two(uint32_t value);
uint32_t swap_endian32(uint32_t value);
uint8_t reverse_bits8(uint8_t value);
uint32_t set_field(uint32_t reg, int pos, int width, uint32_t val);
uint32_t get_field(uint32_t reg, int pos, int width);
int lowest_set_bit_pos(uint32_t value);
uint32_t align_up(uint32_t x, uint32_t align);

#endif /* BIT_MANIPULATION_H */
