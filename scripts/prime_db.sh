#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 0 ] ; then
  echo "ERROR: usage: no arguments" >&2
  exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'run_prime '@notary_etc_PATH@'/scanner_config.txt

exit 1
