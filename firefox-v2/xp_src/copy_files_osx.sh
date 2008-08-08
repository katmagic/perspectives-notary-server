PLUGIN_DIR=../plugin
PLATFORM=Darwin_x86-gcc3
LIB_FILE=Perspectives.dylib

cp IPerspectives.xpt ../dist/components
cp $LIB_FILE ../dist/platform/$PLATFORM/components
cp -rf ../dist/* $PLUGIN_DIR


