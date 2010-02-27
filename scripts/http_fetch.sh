#!@bash_EXEC@

if [ "$#" != 5 -a "$#" != 3 ] ; then
  echo "ERROR: usage: <notary-address> <notary-port> <service-address> <port> <service-type>" >&2
  echo "ERROR: usage: <notary-address> <notary-port> <service-id>" >&2
  exit 1
fi

if [ "$#" == 5 ] ; then

  exec wget -O - -q "http://$1:$2/?host=$3&port=$4&service_type=$5"
  exit 1

elif [ "$#" == 3 ] ; then

  service_id="$3"
  if ! [[ "$service_id" =~ ^[a-z0-9._-]+:[0-9]+,[0-9]+$ ]] ; then
    echo "ERROR: service-id '$service_id' is invalid" >&2
    exit 1
  fi

  host_and_port="${service_id/,*}"
  service_type="${service_id/*,}"
  host="${host_and_port/:*}"
  port="${host_and_port/*:}"

  exec wget -O - -q "http://$1:$2/?host=$host&port=$port&service_type=$service_type"
  exit 1

else
  exit 1
fi

exit 1
