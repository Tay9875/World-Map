# World-Map
Simple C Isometric World map builder

Meant to test isometric skills and BITMAPs, this project deals with isometric tiles and allegro to help build little maps with a variety of tiles.
Project by Tay9875

## Preview
<details>
  <summary>My maps</summary>
  <img src="https://github.com/Tay9875/World-Map/assets/96668181/c02b8d1d-0620-4112-8998-79e2063c63d7"/>
  <img src="https://github.com/Tay9875/World-Map/assets/96668181/6d382e73-07c6-4332-becf-a285c4a84761"/>
</details>

## Installation
Recommendation: Codeblocks

There are only two documents that contain code and the rest are bmps.

Let's start with the code. The main.c file and the header.h file need to be installed in the same project. 
For the BITMAPs, you'll need to create a "isometricTiles" folder in said project.
You can find the set I used in the tileset pack in the credits just below.
Once uploaded, select 30 tiles of your choice in the 50x50 asset pack and paint the background magenta (allows to make it transparent with the Allegro library once debugged), save as a BMP file then rename all the BITMAPs "isometric_pixel_%d" (replace the %d by numbers going from 1 to 30).
The last 5 objects are the bmp files mentioned before hand and also need to be uploaded in the same folder.
Once that is all done, you should have a working project.

### Credits
Tileset pack: https://devilsworkshop.itch.io/big-pixel-isometric-block-pack-free-2d-sprites

## Built with
- C
- Allegro

## Future updates
- [x] Creating a cubic isometric matrix 
- [x] Creating a BITMAP table
- [x] Identifiable position on the map
- [x] Add an element to the map
- [x] Subtract an element from the map
- [x] Possibility to choose out of a variety of elements
- [x] Add objects on the map
- [ ] Save the map in a txt file
- [ ] Charge an already started map from a txt file
- [ ] Map screenshot
#
