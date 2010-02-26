#!@bash_EXEC@

exec >&2

if [ "$#" != 2 ] ; then
  echo "usage: <priv-key-out> <pub-key-out>"
  exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

len=1369

echo
echo "INFO: initializing key pair"

echo "INFO: generating private key"
openssl genrsa -out "$1" "$len"

echo "INFO: generating public key"
openssl rsa -in "$1" -out "$2" -outform PEM -pubout

exit 0
