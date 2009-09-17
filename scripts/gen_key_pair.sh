#!@bash_EXEC@

exec >&2

if [ "$#" != 2 ] ; then
  echo "usage: <priv-key-out> <pub-key-out>"
  exit 1
fi

len=1369

echo "INFO: generating notary key pair"

echo "INFO: generating private key"
openssl genrsa -out "$1" "$len"

echo "INFO: generating public key"
openssl rsa -in "$1" -out "$2" -outform PEM -pubout

exit 0
