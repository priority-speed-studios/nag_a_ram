mkdir -p plugs
#!/usr/bin/env bash
for d in */; do
	if [ "$d" = "plugs/" ]; then
		continue;
	fi
	cd $d;
	gcc -shared -o ../plugs/lib${d%?}.so -fPIC *.c
	cd ..;
done
