/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXTFAttributeHand">
 **/

package org.mozilla.xpcom;

public interface nsIXTFAttributeHandler extends nsISupports
{
  public static final String NS_IXTFATTRIBUTEHANDLER_IID =
    "{72152f7f-7e8d-43fd-8477-3f29ae8d240d}";

  public boolean handlesAttribute(nsIAtom arg1);

  public void setAttribute(nsIAtom arg1, String arg2);

  public void removeAttribute(nsIAtom arg1);

  public String getAttribute(nsIAtom arg1);

  public boolean hasAttribute(nsIAtom arg1);

  public long getAttributeCount();

  public nsIAtom getAttributeNameAt(long arg1);

}
