#!/usr/bin/python

"""
    limgedit - Limg image editor.
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

import sys, os

if len(sys.argv) > 1:
    name = sys.argv[1]
    _bname = os.path.basename(name)
    bname = os.path.splitext(_bname)[0]
    obname = os.path.splitext(name)[0]
    with open(name, "rb") as fp:
        data = fp.read()
    out = """#ifndef {0}
#define {0}

const unsigned char {1}[{2}] = {{
    """.format(bname.upper()+"_H", "b_"+bname, len(data))
    c = 1
    for i in data:
        if c >= len(data):
            out += "0x{:02x}\n".format(i)
        else:
            out += "0x{:02x},".format(i)
            if c%8 == 0 and c>0: out += "\n    "
            else: out += ' '
        c+=1
    out += "};\n\n#endif\n"
    with open(obname+".h", "w") as fp:
        data = fp.write(out)
