/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAutoCompletePopu">
 **/

package org.mozilla.xpcom;

public interface nsIAutoCompletePopup extends nsISupports
{
  public static final String NS_IAUTOCOMPLETEPOPUP_IID =
    "{65f6cd46-22ec-4329-bb3b-bcd1103f2204}";

  public nsIAutoCompleteInput getInput();

  public String getOverrideValue();

  public int getSelectedIndex();

  public void setSelectedIndex(int arg1);

  public boolean getPopupOpen();

  public void openPopup(nsIAutoCompleteInput arg1, int arg2, int arg3, int arg4);

  public void closePopup();

  public void invalidate();

  public void selectBy(boolean arg1, boolean arg2);

}
