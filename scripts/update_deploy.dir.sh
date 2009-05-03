#!/bin/sh

if [ $# != 2 ] 
then 
  echo "usage: <build-dir> <deploy-dir>"
  exit 1
fi

if ! [ -d $1 ] ; then 
  echo "Error, build dir '$1' doesn't exist"
  exit 1 
fi

if  ! [ -d $2 ] ; then 
  echo "Error, deploy dir '$2' doesn't exist"
  exit 1 
fi

if  ! [ -d $2/bin ] ; then 
  echo "Error, '$2'/bin doesn't exist"
  exit 1 
fi

if  ! [ -d $2/scripts ] ; then 
  echo "Error, '$2'/scripts doesn't exist"
  exit 1 
fi

for dir in scripts bin; do cp $1/$dir/* $2/$dir; done

version=`cat SERVER_VERSION`
echo "'$2' now contains version $version of the notary code. Enjoy!" 


