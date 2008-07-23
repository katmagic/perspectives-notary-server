all:
	cp ../config/notary_list.txt plugin
	rm -rf build/
	mkdir build
	cp -r plugin/* build/
	cp -r dist/* build/
	sh -c "cd build/ && zip -r ../Perspectives.xpi *"

test:
	chdir dist
	ls
