/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFXMLSink">
 **/

package org.mozilla.xpcom;

public interface nsIRDFXMLSink extends nsISupports
{
  public static final String NS_IRDFXMLSINK_IID =
    "{eb1a5d31-ab33-11d2-8ec6-00805f29f370}";

  public boolean getReadOnly();

  public void setReadOnly(boolean arg1);

  public void beginLoad();

  public void interrupt();

  public void resume();

  public void endLoad();

  public void addXMLSinkObserver(nsIRDFXMLSinkObserver arg1);

  public void removeXMLSinkObserver(nsIRDFXMLSinkObserver arg1);

}
