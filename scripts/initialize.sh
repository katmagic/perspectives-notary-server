#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

test -d '@notary_db_PATH@' || mkdir -p '@notary_db_PATH@'
test -d '@notary_run_PATH@' || mkdir -p '@notary_run_PATH@'
test -d '@notary_log_PATH@' || mkdir -p '@notary_log_PATH@'

'@notary_bin_PATH@/@notary_bin_PREFIX@'create_keys || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'create_db || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'start_daemons || true

exit 0
