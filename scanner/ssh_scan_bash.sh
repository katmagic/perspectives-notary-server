#!@bash_EXEC@

exec < /dev/null > /dev/null

if ! [ "$#" == 3 ] ; then
	echo "ERROR: usage <service-id> <record-obs-binary> <report-sock-name>" >&2
	exit 1
fi

service_id="$1"
record_bin="$2"
report_sock="$3"
scan_timeout=4
debug_log="/dev/null"


if ! [[ "$service_id" =~ ^[a-z0-9._-]+:[0-9]+,[0-9]+$ ]] ; then
	echo "ERROR: service-id '$service_id' is invalid" >&2
	exit 1
fi

if ! [ -x "$record_bin" ] ; then
	echo "ERROR: '$record_bin' is not a valid binary" >&2
	exit 1
fi


host_and_port="${service_id/,*}"
service_type="${service_id/*,}"
host="${host_and_port/:*}"
port="${host_and_port/*:}"

if ! [ "$service_type" == 1 ] ; then
	echo "WARNING: service type expected to be 1, got '$service_type'" >&2
fi


key_file_1="$( mktemp )"
key_file_2="$( mktemp )"

for key_type in rsa dsa rsa1 ; do
	test -f "$key_file_1" && ssh-keyscan -v -t "$key_type" -p "${port}" -T "$scan_timeout" "$host" < /dev/null > "$key_file_1" 2> "$debug_log" || rm -f "$key_file_1"
	test -f "$key_file_1" && ssh-keygen -v -l -f "$key_file_1" < /dev/null > "$key_file_2" 2> "$debug_log" || rm -f "$key_file_2"
	test -f "$key_file_2" && break
	sleep 0.25
done

if ! [ -f "$key_file_1" -a -f "$key_file_2" ] ; then
	echo "ERROR: error fetching SSH cert" >&2
	rm -f "$key_file_1" "$key_file_2"
	exit 1
fi


fp="$( grep -o -E -e "[0-9a-fA-F]{2}(:[0-9a-fA-F]{2})+" "$key_file_2" | tr '[A-F]' '[a-f]' )"
rm -f "$key_file_1" "$key_file_2"
echo "fp=$fp" > "$debug_log"

if ! [ -n "$fp" ] ; then
	echo "ERROR: fingerprint '$fp' is invalid" >&2
	exit 1
fi


exec "$record_bin" "$host" "$port" "$service_type" "ssh-$key_type" "$fp" "$report_sock"
exit 1
