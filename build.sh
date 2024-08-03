CFLAGS="-Wall -Wextra -Wno-unused-parameter"
RAYINC=~/Workspace/c/raylib/linux/include
STATICLIB=~/Workspace/c/raylib/linux/lib/libraylib.a
STATICLIBW=~/Workspace/c/raylib/win64-mingw/lib/libraylib.a
LIBREFSL="-lGL -lm"
LIBREFSW="-lopengl32 -lgdi32 -lwinmm"
mkdir -p build
gcc $CFLAGS -I$RAYINC -o build/mines main.c mines.c $STATICLIB $LIBREFSL
x86_64-w64-mingw32-gcc $CFLAGS -I$RAYINC -o build/mines.exe main.c mines.c $STATICLIBW $LIBREFSW
