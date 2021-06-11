# gisl

This program is a gis software -- practice for 3d Visualization lecture.

Official website is [gisl](https://www.hotdry.top/gisl/). It can encode and decode text. It can open and write .shp,
.dbf, and .geojson. It also can use .sld to render layer style. And it can convert dem to mesh/tin and read tin/mesh
data. In a word, it is a easy-to-use software.

![image](https://user-images.githubusercontent.com/55835958/116175480-f67d0280-a742-11eb-987f-7db72c9d9d78.png)

## Build

1. git clone

```shell
git clone https://github.com/zy6p/GisL.git
cd GisL
git submodule update --init --recursive
```

2. install depth(ubuntu 20.04)

```shell
sudo su
./scripts/ubuntuGiser.sh
cd extern/abseil-cpp
mkdir build
cmake -B build -S .
cmake --build build --target install
cd ../gmt
cmake -B build -S .
cmake --build build --target install
cd ../..
```

3. build

```shell
cmake -B build -S .
cmake --build build --target install
```

## Feature

1. Easy to use and similar to qgis operations
2. Cross Platform
3. Supported Vector formats include:
    - ESRI Shapefiles
    - GeoJson
4. Supported style formats include:
    - sld
5. Supported Mesh/Tin data.
6. Convert dem/tif to mesh/tin.
    
