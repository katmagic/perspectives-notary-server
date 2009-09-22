#!@bash_EXEC@

exec >&2

if [ "$#" != 2 ] ; then
  echo "usage: <scanner-config> <db-text-file>"
  exit 1
fi

echo
echo "INFO: initializing database"

if ! [ -f "$1" ] ; then
  echo "ERROR: cannot find config file '$1'"
  exit 1
fi

if ! [ -e "$2" ]; then
  echo "ERROR: cannot find db-text-file '$2'"
  exit 1
fi

db_env_fname="$(cat "$1" | grep db_env_fname | awk -F = '{print $2}')"
db_fname="$(cat "$1" | grep db_fname | awk -F = '{print $2}')"
privkey_fname="$(cat "$1" | grep private_key_fname | awk -F = '{print $2}')"

if ! [ -f "$privkey_fname" ] ; then
  echo "ERROR: cannot find private key file '$privkey_fname'"
  exit 1
fi

if ! [ -d "$db_env_fname" ] ; then
  echo "WARNING: cannot find DB environment dir '$db_env_fname'"
  mkdir -p "$db_env_fname"
fi

if ! [ -f "$db_env_fname/$db_fname" ] ; then
  echo "WARNING: cannot find DB file '$db_env_fname/$db_fname'"
fi

# if scanner is running, don't do this, otherwise you will currupt the
# database because there will be two writing processes

#db_writer="scan_db_manager"
#for error in `ps -a | grep -v "grep" | grep $db_writer`; do
#	echo "ERROR: '$db_writer' appears to be running"
#	echo "ERROR: please stop '$db_writer' before running this script"
#	exit 1
#done

echo "INFO: due to per-entry cryptographic signatures, this may take tens of minutes"

'@notary_bin_PATH@/@notary_bin_PREFIX@'file2db "$2" "$db_env_fname" "$db_fname" "$privkey_fname"

exit 0
