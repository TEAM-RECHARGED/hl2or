#!/bin/bash
OS=`uname`
HL2OR_PATH=`game/hl2or/`
if [`$1` == `--models`]; then
    wget https://ia801408.us.archive.org/3/items/hl2oc/OVERCHARGED_2.0.zip
    unzip OVERCHARGED_2.0.zip
    mv OVERCHARGED_2.0 overcharged
    cd overcharged
    mv materials/* $HL2OR_PATH/materials/
    mv models/* $HL2OR_PATH/models/
    rm -rf overcharged
elif [`$1` == `--maps`]; then
    if [ $OS == "Linux"||"Darwin"||"FreeBSD" ]; then
        cp -r ~/.steam/steamapps/common/Half-Life 2/maps/* $HL2OR_PATH/maps/*
    else
        echo "Unknown OS, using Windows."
        cp -r C:/Program Files (x86)/Steam/steamapps/common/Half-Life 2/maps/* $HL2OR_PATHs/maps/*
    fi
Files