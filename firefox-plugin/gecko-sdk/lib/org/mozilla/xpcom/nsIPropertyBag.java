/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPropertyBag">
 **/

package org.mozilla.xpcom;

public interface nsIPropertyBag extends nsISupports
{
  public static final String NS_IPROPERTYBAG_IID =
    "{bfcd37b0-a49f-11d5-910d-0010a4e73d9a}";

  public nsISimpleEnumerator getEnumerator();

  public nsIVariant getProperty(String arg1);

}
