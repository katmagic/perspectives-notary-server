#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "ERROR: usage: no arguments" >&2
  exit 1
fi

. '@notary_libexec_PATH@/@notary_libexec_PREFIX@'check_user

exec '@notary_libexec_PATH@/@notary_libexec_PREFIX@'init_key_pair '@notary_private_key_PATH@' '@notary_public_key_PATH@'

exit 1
