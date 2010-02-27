#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: (no arguments)"
  exit 1
fi

echo
echo "INFO: testing some certificates"

for target in \
		mail.google.com:443,2 \
		mvn.ron.lcs.mit.edu:22,1 \
		cmu.ron.lcs.mit.edu:22,1 \
		mail.info.uvt.ro:443,2 \
		hephaistos.info.uvt.ro:22,1 \
		hotmail.com:443,2 \
; do

  echo
  echo "----- $target --------------------"
  '@notary_bin_PATH@/@notary_bin_PREFIX@'http_fetch '@notary_http_listen_IP@' '@notary_http_listen_PORT@' "$target"
  echo

done

exit 0
