#!/usr/bin/env zsh
set -e

cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo &&
cmake --build build &&

xcrun xctrace record \
  --template "Time Profiler" \
  --launch ./build/phase1 \
  --output phase1.trace \
  --time-limit 10s

open phase1.trace