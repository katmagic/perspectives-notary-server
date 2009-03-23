#/bin/bash 

VERSION='5.0p1'
FILENAME=psv-openssh-${VERSION}.patch
diff -Naur openssh-${VERSION} openssh-${VERSION}-psv > ${FILENAME}

echo "created ${FILENAME}"
 

