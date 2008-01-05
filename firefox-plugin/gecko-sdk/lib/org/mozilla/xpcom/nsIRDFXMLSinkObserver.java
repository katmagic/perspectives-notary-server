/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFXMLSinkObserv">
 **/

package org.mozilla.xpcom;

public interface nsIRDFXMLSinkObserver extends nsISupports
{
  public static final String NS_IRDFXMLSINKOBSERVER_IID =
    "{eb1a5d30-ab33-11d2-8ec6-00805f29f370}";

  public void onBeginLoad(nsIRDFXMLSink arg1);

  public void onInterrupt(nsIRDFXMLSink arg1);

  public void onResume(nsIRDFXMLSink arg1);

  public void onEndLoad(nsIRDFXMLSink arg1);

  public void onError(nsIRDFXMLSink arg1, long arg2, String arg3);

}
