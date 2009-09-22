#!@bash_EXEC@

exec >&2

set -e -u -o pipefail || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'init_db_from_text '@notary_etc_PATH@'/scanner_config.txt /dev/null

exit 1
