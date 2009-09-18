#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_bin_PATH@/@notary_bin_PREFIX@'default_backup_db || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'default_refresh_db || true

exit 0
