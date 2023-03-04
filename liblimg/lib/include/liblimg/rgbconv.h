/*
 * liblimg - Manipulate limg images in C.
 * Copyright (C) 2023  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#ifndef RGBCONV_H
#define RGBCONV_H

#include <stdint.h>

/* uint16_t rgb888torgb565(uint32_t rgb888);

Returns the color rgb888 converted to rgb 565.
*/

uint16_t rgb888torgb565(uint32_t rgb888);

/* uint32_t rgb565torgb888(uint16_t rgb565);

Returns the color rgb565 converted to rgb 888.
*/

uint32_t rgb565torgb888(uint16_t rgb565);

/* void getrgb888(uint32_t rgb888, unsigned char rgb_out[3]);

Puts the r, g, b values into rgb_out, from the rgb 888 color in rgb888.
*/

void getrgb888(uint32_t rgb888, unsigned char rgb_out[3]);

/* void getrgb565(uint16_t rgb565, unsigned char rgb_out[3]);

Puts the r, g, b values into rgb_out, from the rgb 565 color in rgb565.
*/

void getrgb565(uint16_t rgb565, unsigned char rgb_out[3]);

/* uint32_t makergb888(unsigned char rgb888[3]);

Returns a rgb 888 value from r, g, b values in rgb888.
*/

uint32_t makergb888(unsigned char rgb888[3]);

/* uint16_t makergb565(unsigned char rgb565[3]);

Returns a rgb 565 value from r, g, b values in rgb565.
*/

uint16_t makergb565(unsigned char rgb565[3]);

#endif
