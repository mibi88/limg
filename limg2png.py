"""
    limg2png - converts a limg image to a normal png image.
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

if len(sys.argv) < 3:
	print("Command to use this converter :\n $ python3 png2limg.py <limg image> <out png>")
	sys.exit(1)

image = sys.argv[1]
out = sys.argv[2]

try:
	fp = open(image, "rb")
except:
	print("Can't convert this image !")
	sys.exit(2)

magic = fp.read(7).decode("ascii")

if magic != "LIMG-V1":
	print("This is not a limg v1 image !")
	sys.exit(2)

w = int.from_bytes(fp.read(2), byteorder="big")
h = int.from_bytes(fp.read(2), byteorder="big")
p = int.from_bytes(fp.read(1), byteorder="big")

palette = []

for i in range(p):
	color = int.from_bytes(fp.read(2), byteorder="big")
	palette.append(color)

img = Image.new("RGB", (w, h), color = "black")

for y in range(h):
	for x in range(w):
		if p > 0:
			try:
				color = getrgb888_tuple(palette[int.from_bytes(fp.read(1), byteorder="big")])
			except:
				print("There was a small error, the image may look weird !")
		else:
			color = getrgb888_tuple(int.from_bytes(fp.read(2), byteorder="big"))
		img.putpixel((x, y), color)

img.save(out)
fp.close()
