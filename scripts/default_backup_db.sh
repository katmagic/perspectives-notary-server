#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_bin_PATH@/@notary_bin_PREFIX@'run_backup '@notary_etc_PATH@'/scanner_config.txt '@notary_backups_PATH@'

exit 0
