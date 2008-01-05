/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPKCS11Module">
 **/

package org.mozilla.xpcom;

public interface nsIPKCS11Module extends nsISupports
{
  public static final String NS_IPKCS11MODULE_IID =
    "{8a44bdf9-d1a5-4734-bd5a-34ed7fe564c2}";

  public String getName();

  public String getLibName();

  public nsIPKCS11Slot findSlotByName(String arg1);

  public nsIEnumerator listSlots();

}
