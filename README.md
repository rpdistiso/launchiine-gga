## Launchiine-GGA (WIP)

This is a variant of Launchiine that I am making for my local arcade. This version will limit the ability to access applets and user settings to be brick proof for the casual users at said arcade.

## Usage:
([ENVIRONMENT] is a placeholder for the actual environment name)
- Place the `men.rpx` on the SD card in the directory `sd:/wiiu/environments/[ENVIRONMENT]/`
- Load the [MochaPayload](https://github.com/wiiu-env/MochaPayload) via the [EnvironmentLoader](https://github.com/wiiu-env/EnvironmentLoader) (e.g. [Tiramisu](https://github.com/wiiu-env/Tiramisu) or [Aroma](https://github.com/wiiu-env/Aroma))
- Load the Wii U Menu and launchiine should show up instead

## Known Issues
- Random crashes
- The Keyboard input is implemented, but result is ignored
- It's relying on the [AutobootModule](https://github.com/wiiu-env/AutobootModule)
- Probably a lot more

## TODOs
- Non-touch controls (Must touch gamepad then you will be able to use DPad and analog sticks)
- Sound on splashscreen(Fixed sort of)
- Folder support
- Preserve app order after closing/opening launchiine.
- Implement Account selection when no default account is set. 
- Implement update check/way to update games
- Fix search
- Implement all the other stuff the Wii U Menu offers (Account creation, switching between Accounts, set default account etc.)
- Implement ways to launch the original Wii U Menu.

## Building
Install the following dependencies:
- [wut](https://github.com/devkitPro/wut)
- [libgui](https://github.com/wiiu-env/libgui)

Then build via `make`

### Note: You must build libgui from `src/libgui` in this repository, this is required for building with Docker and DevKitPro

## Building using the Dockerfile
It's possible to use a docker image for building. This way you don't need anything installed on your host system.

```
# Build docker image (only needed once)
docker build . -t launchiine-builder

# make 
docker run -it --rm -v ${PWD}:/project launchiine-builder make

# make clean
docker run -it --rm -v ${PWD}:/project launchiine-builder make clean
```

## Credits
Maschell: Libgui, AutoBootModule, original project

Dimok: FreeType and related assets

Steven Bradberry: Greenwood Gamer Arcade assets
