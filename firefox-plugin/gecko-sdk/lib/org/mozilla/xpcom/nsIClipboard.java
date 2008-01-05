/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIClipboard">
 **/

package org.mozilla.xpcom;

public interface nsIClipboard extends nsISupports
{
  public static final String NS_ICLIPBOARD_IID =
    "{8b5314ba-db01-11d2-96ce-0060b0fb9956}";

  public static final int kSelectionClipboard = 0;

  public static final int kGlobalClipboard = 1;

  public void setData(nsITransferable arg1, nsIClipboardOwner arg2, int arg3);

  public void getData(nsITransferable arg1, int arg2);

  public void emptyClipboard(int arg1);

  public boolean hasDataMatchingFlavors(nsISupportsArray arg1, int arg2);

  public boolean supportsSelectionClipboard();

}
