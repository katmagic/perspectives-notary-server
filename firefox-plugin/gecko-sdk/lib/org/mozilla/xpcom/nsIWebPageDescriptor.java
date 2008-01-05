/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebPageDescripto">
 **/

package org.mozilla.xpcom;

public interface nsIWebPageDescriptor extends nsISupports
{
  public static final String NS_IWEBPAGEDESCRIPTOR_IID =
    "{6f30b676-3710-4c2c-80b1-0395fb26516e}";

  public static final long DISPLAY_AS_SOURCE = 1L;

  public static final long DISPLAY_NORMAL = 2L;

  public void loadPage(nsISupports arg1, long arg2);

  public nsISupports getCurrentDescriptor();

}
