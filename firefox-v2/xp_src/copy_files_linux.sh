PLUGIN_DIR=../plugin
PLATFORM=Linux_x86-gcc3
LIB_FILE=Perspectives.so

cp IPerspectives.xpt ../dist/components
cp $LIB_FILE ../dist/platform/$PLATFORM/components
cp -rf ../dist/* $PLUGIN_DIR
