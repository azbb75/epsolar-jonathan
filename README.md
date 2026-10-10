# epever solar display module

The project contains the source code and dashboard website. You can use pre-built binaries or build the source code.

## Downloading pre-build binaries and directly flashing the esp8266 - Recommended for quick firmware updates and Beginners

On windows, download git bash to easily use the esptool once you download it. https://gitforwindows.org/

1. Download the latest pre-build binaries from here: https://bitbucket.org/jonathangoldnauvogt/epever_solar_display/downloads/

2. Extract the zip folder

3. Follow instructions here to download `esptool`: https://github.com/espressif/esptool

4. Put ESP into bootloader mode. Make sure no other serial com port devices are connected to your machine.

5. Open git bash inside the directory where the zip file was extracted by right clicking "Git Bash Here", type 
```bash
esptool.py write_flash 0x000000 firmware.bin 0x300000 spiffs.bin
```
and press enter.

You should see the progress of the firmware downloading. Troubleshoot as necessary using google, or contact customerservice@snektek.com

## Downloading the source code and building 

### Requirements:

1. Download NodeJs from  https://nodejs.org/en/
2. Install `gulp` globally:
```bash
npm install -g gulp
```
3. Install PlatformIO for Visual Studio Code IDE: https://docs.platformio.org/en/latest/ide/pioide.html 
    
    3.1  Install the PIO ESPAsyncTCP Library:  PIO Home -> Libraries -> (search/select ESPAsyncTCP) -> Install

4. Optionally Install PlatformIO Core: https://docs.platformio.org/en/latest/core.html

### Building the source code
The source code is a platform IO project. There are two ways to build and upload the code:

1. Using Visual Studio Code IDE

    1.1 Open the root folder of the project `File -> Open Folder`

    1.2 To Build the code: `Terminal -> Run Task -> PlatformIO:Build`

    1.3 To Upload the code: `Terminal -> Run Task -> PlatformIO:Upload`

    1.4 To Upload the file system image: `Terminal -> Run Task -> PlatformIO:Upload File System Image` 

2. Using Platform IO Core CLI

    2.1 In CLI change directory to the project folder

    2.2 To Build the code: `platformio run`

    2.3 To Upload the code: `platformio run --target upload`

    2.4 To Upload the file system image: `platformio run --target uploadfs `

