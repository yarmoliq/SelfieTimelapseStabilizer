# Selfie Timelapse Stabilizer

This smol program will take an array of images (selfies) and stabilize your face :) so it is in the same positions across all frames.

## Build

### Dependencies:
- [opencv](https://github.com/opencv/opencv) + [opencv_contrib](https://github.com/opencv/opencv_contrib)
- [exiv2](https://github.com/Exiv2/exiv2)
- ffmpeg

To build the project run:
```sh
./build.sh
```
## Use

To use the program run it with the following arguments:
```sh
build/sts path/to/referencePhoto.jpg path/to/inputDir/ path/to/outputDir/
```
where:

`path/to/referencePhoto.jpg` - path to the reference photo, which will determine the position of the face.<br/>
`path/to/inputDir/` - path to the directory with imges that you want to proccess.<br/>
`path/to/outputDir/` - path to the directory that will store the proccessed images.<br/>

> :warning: **Note that you have to have the `/` in the end of your directory** because the program is in early development and we haven't implemented such a nicety yet.