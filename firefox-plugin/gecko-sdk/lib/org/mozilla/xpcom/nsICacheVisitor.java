/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheVisitor">
 **/

package org.mozilla.xpcom;

public interface nsICacheVisitor extends nsISupports
{
  public static final String NS_ICACHEVISITOR_IID =
    "{f8c08c4b-d778-49d1-a59b-866fdc500d95}";

  public boolean visitDevice(String arg1, nsICacheDeviceInfo arg2);

  public boolean visitEntry(String arg1, nsICacheEntryInfo arg2);

}
