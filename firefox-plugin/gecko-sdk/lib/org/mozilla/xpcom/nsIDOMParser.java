/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMParser">
 **/

package org.mozilla.xpcom;

public interface nsIDOMParser extends nsISupports
{
  public static final String NS_IDOMPARSER_IID =
    "{4f45513e-55e5-411c-a844-e899057026c1}";

  public nsIDOMDocument parseFromString(String arg1, String arg2);

  public nsIDOMDocument parseFromBuffer(short[] arg1, long arg2, String arg3);

  public nsIDOMDocument parseFromStream(nsIInputStream arg1, String arg2, int arg3, String arg4);

}
