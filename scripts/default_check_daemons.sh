#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_daemon http_server || true
'@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_daemon db_manager || true
'@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_daemon ondemand_listener || true

exit 0
