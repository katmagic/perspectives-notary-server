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
mkdir $2/bin
mkdir $2/run
mkdir $2/scripts 

for f in notary-http/notary-http notary-scanner/notary-db-manager notary-scanner/report-observation
do 
 	cp $1/$f $2/bin
done 

cp $1/notary-scanner/scripts/* $2/scripts

# copy utilities over
for f in db2file file2db db_search signature_util request_scan
do
	cp $1/utilities/$f $2/bin
done 

for dir in db_env log keys; do mkdir $2/$dir; done

for dir in scripts config; do cp -r $1/$dir $2; done

$2/scripts/gen_key_pair.sh $2/keys/private.pem $2/keys/public.pem

rm $2/config/http_notary_list.txt

echo "127.0.0.1:15217" > $2/config/http_notary_list.txt
cat $2/keys/public.pem  >> $2/config/http_notary_list.txt

$2/bin/file2db /dev/null $2/db_env/ notary.db $2/keys/private.pem

version=`cat SERVER_VERSION`
echo "'$2' now contains a notary version $version deployment. Enjoy!" 


