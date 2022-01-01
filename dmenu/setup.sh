#!/usr/bin/env sh

set -e

echo "Setting up ST"

if [ -f source/config.h ]; then
    echo "backing up config.h"
    mv -v source/config.h config.h
fi

# Apply patches
cd source

# reset everything
echo "Cleaning up working tree"
git reset --hard HEAD
git clean -df *

echo "Applying patches"

for file in ../patches/*.diff; do
    echo "Aplying $file"
    patch -p1 < $file
done

echo "Cleaning up original files"
find . -type f -name "*.orig" -exec rm {} +

cd ..

if [ -f config.h ]; then
    echo "restoring config.h"
    cp config.h source/config.h
fi

if [ ! -f source/config.h ]; then
    echo "Creating default config file"
    cp source/config.def.h source/config.h
fi

echo "Good to go!"