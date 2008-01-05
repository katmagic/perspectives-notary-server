/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIClipboardCommand">
 **/

package org.mozilla.xpcom;

public interface nsIClipboardCommands extends nsISupports
{
  public static final String NS_ICLIPBOARDCOMMANDS_IID =
    "{b8100c90-73be-11d2-92a5-00105a1b0d64}";

  public boolean canCutSelection();

  public boolean canCopySelection();

  public boolean canCopyLinkLocation();

  public boolean canCopyImageLocation();

  public boolean canCopyImageContents();

  public boolean canPaste();

  public void cutSelection();

  public void copySelection();

  public void copyLinkLocation();

  public void copyImageLocation();

  public void copyImageContents();

  public void paste();

  public void selectAll();

  public void selectNone();

}
