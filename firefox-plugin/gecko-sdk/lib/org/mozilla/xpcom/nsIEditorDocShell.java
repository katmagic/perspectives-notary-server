/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditorDocShell">
 **/

package org.mozilla.xpcom;

public interface nsIEditorDocShell extends nsISupports
{
  public static final String NS_IEDITORDOCSHELL_IID =
    "{3bdb8f01-f141-11d4-a73c-fba4aba8a3fc}";

  public nsIEditor getEditor();

  public void setEditor(nsIEditor arg1);

  public boolean getEditable();

  public boolean getHasEditingSession();

  public void makeEditable(boolean arg1);

}
