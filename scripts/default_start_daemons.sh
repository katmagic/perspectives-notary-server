#!/bin/sh

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

'@notary_bin_PATH@/@notary_bin_PREFIX@'start_http_server '@notary_etc_PATH@'/http_server_config.txt
'@notary_bin_PATH@/@notary_bin_PREFIX@'start_db_manager '@notary_etc_PATH@'/scanner_config.txt
'@notary_bin_PATH@/@notary_bin_PREFIX@'start_ondemand_listener '@notary_etc_PATH@'/scanner_config.txt

exit 0
