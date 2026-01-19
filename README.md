# atlas
Texture atlas command-line tool

```
atlas replace <src> <dest> <cx> <cy> <c> [--force] [--overwrite] [--mask]
  Replaces one cell in destination atlas image.
  src: source image png filename
  dest: destination image png filename
  cx: number of cells in x
  cy: number of cells in y
  c: cell to replace [0 .. cx * cy)
  --force: continue despite misgivings
  --overwrite: overwrite destination image
  --mask: convert image into a mask (RBG->alpha)
```
Replaces a cell in the destination atlas with the source image. 

## How to build
1. Clone this repo
2. Clone lo-res library in peer directory
3. Build lo-res library
4. Build atlas
```
git clone git@github.com:amju-games/atlas.git
git clone git@github.com:amju-games/lo-res.git
cd lo-res
make
cd ../atlas
make
```
