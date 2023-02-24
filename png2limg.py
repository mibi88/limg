"""
    png2limg - converts a normal png image (or any other image type
    supported by PIL) to a limg image.
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

from rgbconv import *
from PIL import Image
import sys

def get_color_palette(rgb_img, w, h):
	palette = []
	for y in range(h):
		for x in range(w):
			color = makergb565(getrgb565_tuple(makergb888(rgb_img.getpixel((x, y)))))
			if not color in palette:
				palette.append(color)
	return palette

if len(sys.argv) < 3:
	print("Command to use this converter :\n $ python3 png2limg.py <png image> <out limg>")
	sys.exit(1)

image = sys.argv[1]
out = sys.argv[2]

try:
	img = Image.open(image)
except:
	print("Can't convert this image !")
	sys.exit(2)
rgb_img = img.convert("RGB")
w, h = rgb_img.size
fp = open(out, "wb")

fp.write("LIMG-V1".encode("ascii"))
fp.write(w.to_bytes(2, "big"))
fp.write(h.to_bytes(2, "big"))

palette = get_color_palette(rgb_img, w, h)

if len(palette) <= 256:
	p = len(palette)
else:
	p = 0

fp.write(p.to_bytes(1, "big"))

if p > 0:
	for i in palette:
		fp.write(i.to_bytes(2, "big"))

for y in range(h):
	for x in range(w):
		color = makergb565(getrgb565_tuple(makergb888(rgb_img.getpixel((x, y)))))
		if p > 0:
			pos = palette.index(color)
			fp.write(pos.to_bytes(1, "big"))
		else:
			fp.write(color.to_bytes(2, "big"))

fp.close()
