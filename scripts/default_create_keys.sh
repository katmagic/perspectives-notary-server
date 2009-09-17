#!@bash_EXEC@

exec >&2

if [ "$#" != 0 ] ; then
  echo "usage: no arguments"
  exit 1
fi

exec '@notary_bin_PATH@/@notary_bin_PREFIX@'gen_key_pair '@notary_private_key_PATH@' '@notary_public_key_PATH@'

exit 0
