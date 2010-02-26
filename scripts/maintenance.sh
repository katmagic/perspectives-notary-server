#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

'@notary_bin_PATH@/@notary_bin_PREFIX@'prime_db || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'backup_db || true
'@notary_bin_PATH@/@notary_bin_PREFIX@'refresh_db || true

exit 0
