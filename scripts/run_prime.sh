#!@bash_EXEC@

exec >&2

if [ "$#" != 1 ] ; then
  echo "ERROR: usage: <scanner-config>" >&2
  exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

echo >&2
echo "INFO: priming database" >&2

if ! [ -f $1 ] ; then
    echo "ERROR: cannot find config file '$1'" >&2
    exit 1
fi

db_env_fname="$(cat "$1" | grep db_env_fname | awk -F = '{print $2}')"

if ! [ -d "$db_env_fname" ] ; then
    echo "ERROR: cannot find DB environment dir '$db_env_fname'" >&2
    exit 1
fi

'@notary_libexec_PATH@/@notary_libexec_PREFIX@'db_prime "$db_env_fname"

exit 0
