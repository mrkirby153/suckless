#!/usr/bin/env sh

set -e

echo "Setting up ST"

if [ -f source/config.h ]; then
    echo "backing up config.h"
    mv -v source/config.h config.h
fi

# Apply patches
cd source

git config commit.gpgsign false

# reset everything
echo "Cleaning up working tree"
git reset --hard origin/HEAD
git clean -df *

echo "Applying patches"

for file in ../patches/*.diff; do
    git am -3 --whitespace=fix "$file"
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