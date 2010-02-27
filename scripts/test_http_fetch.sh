#!@bash_EXEC@

if [ "$#" != 0 ] ; then
  echo "ERROR: usage: no arguments" >&2
  exit 1
fi

echo >&2
echo "INFO: testing some certificates" >&2

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
  '@notary_bin_PATH@/@notary_bin_PREFIX@'http_fetch 'http://@notary_http_listen_IP@:@notary_http_listen_PORT@/' "$target"
  echo

done

exit 0
