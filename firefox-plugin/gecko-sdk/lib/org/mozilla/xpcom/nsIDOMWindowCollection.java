/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMWindowCollect">
 **/

package org.mozilla.xpcom;

public interface nsIDOMWindowCollection extends nsISupports
{
  public static final String NS_IDOMWINDOWCOLLECTION_IID =
    "{a6cf906f-15b3-11d2-932e-00805f8add32}";

  public long getLength();

  public nsIDOMWindow item(long arg1);

  public nsIDOMWindow namedItem(String arg1);

}
