#!/usr/bin/env sh

set -e

echo "Setting up ST"

if [ -f source/config.h ]; then
    echo "backing up config.h"
    mv -v source/config.h config.h
fi

# Apply patches
pushd source

# reset everything
echo "Cleaning up working tree"
git reset --hard HEAD
git clean -df *

if [ "$(git config commit.gpgsign)" != "false" ]; then
    echo "Disabling gpg signing"
    git config commit.gpgsign false
fi

popd

echo "Resetting submodule"
git submodule update source

pushd source

echo "Applying patches"

for file in ../patches/*.diff; do
    git am -3 --whitespace=fix "$file"
done

popd

if [ -f config.h ]; then
    echo "restoring config.h"
    cp config.h source/config.h
fi

if [ ! -f source/config.h ]; then
    echo "Creating default config file"
    cp source/config.def.h source/config.h
fi

echo "Good to go!"