#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Copying dynamic libraries to /usr/lib..."
echo Robil12 | sudo -S cp -v $DIR/comp/lib* /usr/lib
sudo ldconfig

echo "Copying dynamic libraries to Unity..."
cp -v $DIR/comp/lib* ~/ConvoyUnity/Assets/Plugins

echo "Copying Wrappers to Unity..."
cp -v $DIR/../../external_files/*Wrapper.cs ~/ConvoyUnity/Assets/Scripts/LibWrappers/

echo "Copying Configuration files to home directory..."
#sudo mkdir -p ~/simConfigs
#sudo cp -v $DIR/../../external_files/*.conf ~/simConfigs
