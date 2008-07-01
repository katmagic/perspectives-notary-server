PLUGIN_DIR=../plugin
PLATFORM=Linux_x86-gcc3
LIB_FILE=Perspectives.so

cp IPerspectives.xpt $PLUGIN_DIR/components
cp IPerspectives.xpt ../dist/components
cp $LIB_FILE $PLUGIN_DIR/platform/$PLATFORM/components
cp $LIB_FILE ../dist/platform/$PLATFORM/components
