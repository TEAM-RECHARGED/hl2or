#!/bin/bash
OS=`uname`
if [`$1` == `--models`]; then
    wget https://ia801408.us.archive.org/3/items/hl2oc/OVERCHARGED_2.0.zip
    unzip OVERCHARGED_2.0.zip
    mv OVERCHARGED_2.0 overcharged
    cd overcharged
    mv materials/* game/hl2or/materials/
    mv models/* game/hl2or/models/
elif [`$1` == `--maps`]; then
    if [ $OS == "Linux" ]; then
        cp -r ~/.steam/steamapps/common/Half-Life 2/maps/* game/hl2or/maps/*
    else
        echo "Unknown OS, using Windows."
        cp -r C:/Program Files (x86)/Steam/steamapps/common/Half-Life 2/maps/* game/hl2or/maps/*
    fi
fi