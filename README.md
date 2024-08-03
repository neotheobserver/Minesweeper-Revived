# Minesweeper Revived

## How to run

### Linux

```sh
git clone REPO_URL
```

```sh
cd REPO_DIR/build
```

```sh
chmod +x mines
```

```sh
./mines
```

### Windows

Download the repo and run the `mines.exe` file from build directory if window will allow it. I promise its not malware/spyware.

## How to play (rules)

It is a 8x8 field. There are 10 totals mines. Your task is to flag the tiles with mine while opening up safe tiles. You can right click to open the tile and left click to flag the tile.

`The number shown when you click the tile is the number of mines around the tile.`
You win the game when you have flagged all the mines and opened up all the safe tiles.

## How to Build (Optional)

You need to have the raylib source files to compile or the compiled static or dynamic raylib library beforehand to build.

### Linux

Modify the `build.sh` file and provide path to your raylib static library.
Modify the `main.c` to provide correct path for raygui.h header file
Finally run:

```sh
chmod +x build.sh
./build.sh
```

### Windows

If you are on windows you are on your own. If you are on linux compiling for windows, you can modify the `build.sh` file and uncomment the build command for windows.
Also make sure you change the path for the static raylib files as well as raygui.h

## Acknowlegement

Recently, one of my friends at work introduced me to minesweeper. I remember playing it as a child without care and just pressing everything randomly and getting bored. However, this time it was different. He taught me the rules and the game seemed so much more fun. I was so into the game that I played the game till 12 in the night with my girl friend who enjoyed the game equally. It made me very happy that she enjoyed it as much as I did.

The development of the game would not have been possible without the raylib library So I would like to extend my gratitude to the developers. I am not sure about the legalities or else I would have posted the static raylib library required to build in the repo itself.
