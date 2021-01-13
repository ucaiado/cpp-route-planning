#!/bin/bash
BuildDir="build"

cd /CppND-Route-Planning-Project/
if [ ! -d "$BuildDir" ]; then
mkdir $BuildDir
fi
cd $BuildDir

# build project
cmake ..
make

# run A*
./OSM_A_star_search -f ../map.osm
