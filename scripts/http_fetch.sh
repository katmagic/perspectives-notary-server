#!@bash_EXEC@

if [ "$#" != 4 -a "$#" != 2 ] ; then
  echo "ERROR: usage: <notary-url> <service-address> <port> <service-type>" >&2
  echo "ERROR: usage: <notary-url> <service-id>" >&2
  exit 1
fi

if [ "$#" == 4 ] ; then

  exec wget -O - -q "$1?host=$2&port=$3&service_type=$4"
  exit 1

elif [ "$#" == 2 ] ; then

  service_id="$2"
  if ! [[ "$service_id" =~ ^[a-z0-9._-]+:[0-9]+,[0-9]+$ ]] ; then
    echo "ERROR: service-id '$service_id' is invalid" >&2
    exit 1
  fi

  host_and_port="${service_id/,*}"
  service_type="${service_id/*,}"
  host="${host_and_port/:*}"
  port="${host_and_port/*:}"

  exec wget -O - -q "$1?host=$host&port=$port&service_type=$service_type"
  exit 1

else
  exit 1
fi

exit 1
