#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

exec '@notary_bin_PATH@/@notary_bin_PREFIX@'run_scan db '@notary_etc_PATH@'/scanner_config.txt 6 6

exit 0
