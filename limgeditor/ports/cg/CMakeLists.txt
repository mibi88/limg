# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(MyAddin)

include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)
find_package(JustUI 1.0 REQUIRED)

execute_process(COMMAND python3 ./conv/binheader.py ./data/milifont.limg WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})


set(SOURCES
  ../../src/main.c
  ../../src/draw_limg.c
  ../../src/gfx.c
  ../../src/popups.c
  ../../src/keyboard.c
  ../../src/file.c
  ../../src/error.c
  ../../src/text.c
  ../../src/image.c
  ../../src/menu.c
  src/filechooser.c
  ../../src/textbox.c
  ../../src/textinput.c
  ../../src/editor.c
  # liblimg
  ../../../liblimg/lib/src/liblimg.c
  ../../../liblimg/lib/src/rgbconv.c
  # libudraw
  uDraw/src/libudraw.c
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_cg
  # ...
)

include_directories(../../../liblimg/lib/include/liblimg/)
include_directories(uDraw/include/libudraw)

fxconv_declare_assets(${ASSETS} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wpedantic -Wextra -lSDL -Os)
target_link_libraries(myaddin Gint::Gint JustUI::JustUI)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "Limgedit.g3a"
    NAME "Limg editor" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
endif()
