/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWritableProperty">
 **/

package org.mozilla.xpcom;

public interface nsIWritablePropertyBag extends nsIPropertyBag
{
  public static final String NS_IWRITABLEPROPERTYBAG_IID =
    "{96fc4671-eeb4-4823-9421-e50fb70ad353}";

  public void setProperty(String arg1, nsIVariant arg2);

  public void deleteProperty(String arg1);

}
