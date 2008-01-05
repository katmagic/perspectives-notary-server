#!/bin/bash

dir=$PWD

cleanup()
{
    echo "Cleaning.. "
    rm -rf Perspectives_1.0.0.xpi
    cd $dir/_xpcom
    make clean 2> /dev/null 1>&2 
    if [ $? != 0 ]; then 
        echo "Cleaning _xpcom failed"; 
    fi    
    cd $dir/plugin/chrome
    rm -rf perspectives.jar
}

create_plugin()
{
    echo "Creating Plugin... "
    cd $dir/_xpcom
    make 2> /dev/null 1>&2 

    if [ $? != 0 ]; then 
        echo "Make _xpcom failed"; 
        exit 1;
    fi  

    cd $dir/plugin/chrome
    jar cf perspectives.jar content/ locale/ 

    if [ $? != 0 ]; then 
        echo "Making Chrome jar failed";
        exit 1;
    fi  

    cp $dir/_xpcom/Perspectives.so $dir/plugin/platform/Linux_x86-gcc3/components  &&
                cp $dir/_xpcom/Perspectives.so $dir/plugin/platform/linux-gnu_x86-gcc3/components 
    
    if [ $? != 0 ]; then 
        echo "Copy of Component Library failed"; 
        exit 1;
    fi  

    mv $dir/plugin/chrome/content $dir
    mv $dir/plugin/chrome/locale  $dir
    cd $dir/plugin
    zip -qr $dir/Perspectives_1.0.0.xpi * 
    
    if [ $? != 0 ]; then 
        echo "Zipping Plugin failed"; 
    fi    

    mv $dir/content $dir/plugin/chrome
    mv $dir/locale $dir/plugin/chrome

    cd $dir
}

if [ $# -gt 2 ]; then
    echo 1>&2 Usage: $0 [quick | clean]  
fi

if [ "$1"x == "x" -o "$1" == "clean" ]; then
    cleanup
fi    

if [ "$1"x == "x" -o "$1" == "quick" ]; then
    create_plugin
fi

