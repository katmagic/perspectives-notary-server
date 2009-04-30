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

if  [ -d $2 ] ; then 
  echo "Error, deploy dir '$2' already exists, refusing to overwrite"
  exit 1 
fi

mkdir $2
for dir in db_env log keys; do mkdir $2/$dir; done

for dir in scripts bin config; do cp -r $1/$dir $2; done

$2/scripts/gen_key_pair.sh $2/keys/private.pem $2/keys/public.pem

rm $2/config/notary_list.txt
echo "127.0.0.1 15217" > $2/config/notary_list.txt
cat $2/keys/public.pem  >> $2/config/notary_list.txt

rm $2/config/http_notary_list.txt
echo "127.0.0.1:15217" > $2/config/http_notary_list.txt
cat $2/keys/public.pem  >> $2/config/http_notary_list.txt

$2/bin/file2db /dev/null $2/db_env/ notary.db $2/keys/private.pem md5

echo "'$2' now contains a notary deployment. Enjoy!" 


