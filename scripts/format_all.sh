#!/bin/bash
abspath=$(cd ${0%/*} && echo $PWD/${0##*/})
projroot=$(cd "$(dirname abspath)" && echo $PWD)

source_folders=("src" "tests")
for i in ${source_folders[@]}; do
    for srcfile in $(find $projroot/$i -iname "*.h" -o -iname "*.cpp" -iname "*.hpp" -iname "*.cc"); do
        clang-format -i $srcfile
    done
done
