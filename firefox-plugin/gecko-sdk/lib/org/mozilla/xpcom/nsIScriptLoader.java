/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptLoader">
 **/

package org.mozilla.xpcom;

public interface nsIScriptLoader extends nsISupports
{
  public static final String NS_ISCRIPTLOADER_IID =
    "{339a4eb5-dac6-4034-8c43-f4f8c645ce57}";

  public void init(nsISupports arg1);

  public void dropDocumentReference();

  public void addObserver(nsIScriptLoaderObserver arg1);

  public void removeObserver(nsIScriptLoaderObserver arg1);

  public void processScriptElement(nsISupports arg1, nsIScriptLoaderObserver arg2);

  public nsISupports getCurrentScript();

  public boolean getEnabled();

  public void setEnabled(boolean arg1);

}
