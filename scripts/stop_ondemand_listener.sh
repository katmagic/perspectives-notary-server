#!/bin/sh

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

f='@notary_run_PATH@'/ondemand_listener.pid

if ! [ -f "$f" ] ; then
  echo "ERROR: cannot find pid file '$f'; please kill manually"
  exit 1
fi

echo "INFO: stopping ondemand_listener"

kill "$(cat "$f")"
rm "$f"

exit 0
