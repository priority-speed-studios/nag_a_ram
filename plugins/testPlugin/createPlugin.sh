#!/usr/bin/env bash
gcc -shared -o lib$1.so -fPIC *.c
