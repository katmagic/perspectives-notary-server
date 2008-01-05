/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditingSession">
 **/

package org.mozilla.xpcom;

public interface nsIEditingSession extends nsISupports
{
  public static final String NS_IEDITINGSESSION_IID =
    "{d39fd2b4-3978-45d2-a4be-ba448171b61b}";

  public static final int eEditorOK = 0;

  public static final int eEditorCreationInProgress = 1;

  public static final int eEditorErrorCantEditMimeType = 2;

  public static final int eEditorErrorFileNotFound = 3;

  public static final int eEditorErrorCantEditFramesets = 8;

  public static final int eEditorErrorUnknown = 9;

  public long getEditorStatus();

  public void makeWindowEditable(nsIDOMWindow arg1, String arg2, boolean arg3);

  public boolean windowIsEditable(nsIDOMWindow arg1);

  public nsIEditor getEditorForWindow(nsIDOMWindow arg1);

  public void setupEditorOnWindow(nsIDOMWindow arg1);

  public void tearDownEditorOnWindow(nsIDOMWindow arg1);

  public void setEditorOnControllers(nsIDOMWindow arg1, nsIEditor arg2);

}
