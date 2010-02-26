
if [ "${USER}" != '@notary_USER@' ] ; then
  if [ "${USER}" == 'root' ] ; then
    echo "WARNING: script runned as root which is unadvised"
    echo "INFO: switching to proper user @notary_USER@"
    echo "INFO: there might be problems if the original command contains spaces"
    echo
    exec su '@notary_USER@' -c "${0} $*"
    exit 1
  else
    echo "WARNING: script runned as a different user than the proper one (@notary_USER@)"
    echo
  fi
fi

