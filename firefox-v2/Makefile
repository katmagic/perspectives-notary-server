all:
	cp -f ../config/notary_list.txt plugin
	rm -rf build/
	mkdir build
	cp -fr plugin/* build/
	cp -fr dist/* build/
	sh -c "cd build/ && zip -r ../Perspectives.xpi *"

test:
	chdir dist
	ls
