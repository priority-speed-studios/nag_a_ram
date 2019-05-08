#!/usr/bin/env bash
mkdir -p plugs
for d in */; do
	if [ "$d" = "plugs/" ]; then
		continue;
	fi
	cd $d;
	gcc -shared -o ../plugs/lib${d%?}.so -fPIC *.c $(cat libs.txt 2>/dev/null) 2>/dev/null
	cd ..;
done
cp -r ./plugs $1
