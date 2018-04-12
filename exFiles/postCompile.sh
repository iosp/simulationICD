#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Copying dynamic libraries to /usr/lib..."
echo Robil12 | sudo -S cp -v ../comp/lib* /usr/lib
sudo ldconfig

echo "Copying dynamic libraries to Unity..."
cp -v ../comp/lib* /usr/lib ~/ConvoyUnity/Assets/Plugins

echo "Copying Wrappers to Unity..."
cp -v $DIR/*Wrapper.cs ~/ConvoyUnity/Assets/Scripts/

echo "Copying Configuration files to home directory..."
sudo mkdir -p ~/simConfigs
sudo cp -v $DIR/*.conf ~/simConfigs
