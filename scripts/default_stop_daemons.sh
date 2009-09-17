#!/bin/sh

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

@notary_bin_PATH@/@notary_bin_PREFIX@stop_http_server
@notary_bin_PATH@/@notary_bin_PREFIX@stop_db_manager
@notary_bin_PATH@/@notary_bin_PREFIX@stop_ondemand_listener

exit 0
