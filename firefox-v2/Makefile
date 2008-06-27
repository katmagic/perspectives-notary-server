all:
	cp ../config/notary_list.txt plugin
	cp -rf plugin/* dist/
	sh -c "cd dist/ && zip -r ../perspectives.xpi *"

test:
	chdir dist
	ls
