#!/bin/bash
echo "] C H A O S"
sleep 1
echo "] B U I L D"
sleep 1
echo "] T O O L."
sleep 1
platform="linux"
helpdialog()
{
    echo "CHAOS BUILD TOOL | HELP DIALOG"
    echo "--linux | Compiles for Linux."
    echo "--android | Compiles for Android."
    echo "--help | Displays help dialog."
    echo "--vpcconvert (requires path to vpc name) | Converts the vpc script"
}

if [ "$1" == "--android" ]; then
    platform="android"
elif [ "$1" == "--linux" ] || [ -z "$1" ]; then
    platform="linux"
elif ["$1" == "--help"]; then
    helpdialog
else
    echo "Invalid argument. Use --android or --linux."
    exit 1
fi

echo "Selected platform: $platform"

if [ "$platform" == "linux" ]; then
    if [ "$2" == "--vpcconvert"]; then
        echo "\$macro" >> $3.cbt
elif [ "$platform" == "android" ]; then
    echo "Android support coming soon"
fi
