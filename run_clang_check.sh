#!/bin/bash

cd $(dirname $0)
find `pwd` -iname '*.cc' | xargs clang-tidy -checks=modernize*  -p=./build/ -header-filter=.*