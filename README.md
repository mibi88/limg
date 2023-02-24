# limg
A small format for images with rgb565 colors

## The image format

LIMG v1 is big endian
```
|---------------------------------------------------|
| Bytes    |                                        |
|----------|----------------------------------------|
| 7        | Magic "LIMG-V1"                        |
|----------|----------------------------------------|
| 2        | uint16_t image width                   |
|----------|----------------------------------------|
| 2        | uint16_t image height                  |
|----------|----------------------------------------|
| 1        | 0 if more than 256 colors, or palette  |
|          | size.                                  |
|---------------------------------------------------|
   |
   |--> <= 256 colors |
                      V
|---------------------------------------------------|
| 3        | uint16_t color                         |
|---------------------------------------------------|

|---------------------------------------------------|
| 2xpixels > uint16_t color or if <= 256 colors |   |
|    or    |                                    V   |
| 1xpixels >                   uint8_t color index  |
|---------------------------------------------------|
```
