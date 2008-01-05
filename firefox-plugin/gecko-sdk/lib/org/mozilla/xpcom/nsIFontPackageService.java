/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFontPackageServi">
 **/

package org.mozilla.xpcom;

public interface nsIFontPackageService extends nsISupports
{
  public static final String NS_IFONTPACKAGESERVICE_IID =
    "{6712fdd2-f978-11d4-a144-005004832142}";

  public void setHandler(nsIFontPackageHandler arg1);

  public void fontPackageHandled(boolean arg1, boolean arg2, String arg3);

}
