#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_bin_PATH@/@notary_bin_PREFIX@'default_create_keys || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'default_create_db || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'default_start_daemons || true

exit 0
