#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_bin_PATH@/@notary_bin_PREFIX@'start_daemon http_server '@notary_etc_PATH@'/http_server_config.txt || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'start_daemon db_manager '@notary_etc_PATH@'/scanner_config.txt || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'start_daemon ondemand_listener '@notary_etc_PATH@'/scanner_config.txt || true

exit 0
