/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirIndexListener">
 **/

package org.mozilla.xpcom;

public interface nsIDirIndexListener extends nsISupports
{
  public static final String NS_IDIRINDEXLISTENER_IID =
    "{fae4e9a8-1dd1-11b2-b53c-8f3aa1bbf8f5}";

  public void onIndexAvailable(nsIRequest arg1, nsISupports arg2, nsIDirIndex arg3);

  public void onInformationAvailable(nsIRequest arg1, nsISupports arg2, String arg3);

}
