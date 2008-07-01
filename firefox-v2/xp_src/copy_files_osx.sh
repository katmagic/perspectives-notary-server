PLUGIN_DIR=../plugin
PLATFORM=Darwin_x86-gcc3
LIB_FILE=Perspectives.dylib

cp IPerspectives.xpt $PLUGIN_DIR/components
cp IPerspectives.xpt ../dist/components
cp $LIB_FILE $PLUGIN_DIR/platform/$PLATFORM/components
cp $LIB_FILE ../dist/platform/$PLATFORM/components


