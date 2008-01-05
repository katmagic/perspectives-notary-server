/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDNSListener">
 **/

package org.mozilla.xpcom;

public interface nsIDNSListener extends nsISupports
{
  public static final String NS_IDNSLISTENER_IID =
    "{41466a9f-f027-487d-a96c-af39e629b8d2}";

  public void onLookupComplete(nsICancelable arg1, nsIDNSRecord arg2, long arg3);

}
