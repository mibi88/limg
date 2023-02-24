"""
    rgbconv - converts rgb888 and rgb565 from the one to the other.
    Copyright (C) 2023  Mibi88
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see https://www.gnu.org/licenses/.
"""

def getrgb888_tuple(rgb565):
	r = rgb565>>11
	g = (rgb565>>5) - (r<<6)
	b = rgb565 - (rgb565>>5<<5)
	return (r*8, g*4, b*8)

def getrgb565_tuple(rgb888):
	r = rgb888>>16
	g = (rgb888>>8) - (r<<8)
	b = rgb888 - (rgb888>>8<<8)
	return (r//8, g//4, b//8)

def makergb888(rgb_tuple):
	c = rgb_tuple[2]
	c += rgb_tuple[1]<<8
	c += rgb_tuple[0]<<16
	return c

def makergb565(rgb_tuple):
	c = rgb_tuple[2]
	c += rgb_tuple[1]<<5
	c += rgb_tuple[0]<<11
	return c

""" EXAMPLE
rgb888 = getrgb888_tuple(0xFFE0)
print(rgb888)
print("#{:06x}".format(makergb888(rgb888)))
rgb565 = getrgb565_tuple(0xFFFF00)
print(rgb565)
print("#{:04x}".format(makergb565(rgb565)))
"""
