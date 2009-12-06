#!@bash_EXEC@

exec >&2

set -e -u || exit 1

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'run_backup '@notary_etc_PATH@'/scanner_config.txt '@notary_backups_PATH@'

exit 1
