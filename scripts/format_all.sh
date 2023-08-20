#!/bin/bash
abspath=$(cd ${0%/*} && echo $PWD/${0##*/})
projroot=$(cd "$(dirname abspath)" && echo $PWD)

source_folders=("base" "server" "common")
for i in ${source_folders[@]}; do
    find $projroot/$i -iname "*.h" -o -iname "*.cpp" -iname "*.hpp" -iname "*.cc" | xargs clang-format -i
done
