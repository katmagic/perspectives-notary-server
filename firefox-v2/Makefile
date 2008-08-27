all:
	cp -f ../config/notary_list.txt plugin
	rm -rf build/
	mkdir build
	cp -fr plugin/* build/
	cp -fr dist/* build/
	sh -c "cd build/ && zip -r ../Perspectives.xpi * -x *\.svn*" 
	rm -rf build	

test:
	chdir dist
	ls
