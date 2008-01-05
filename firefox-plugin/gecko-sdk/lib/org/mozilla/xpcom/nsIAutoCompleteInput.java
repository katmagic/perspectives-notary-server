/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAutoCompleteInpu">
 **/

package org.mozilla.xpcom;

public interface nsIAutoCompleteInput extends nsISupports
{
  public static final String NS_IAUTOCOMPLETEINPUT_IID =
    "{e312267f-8f57-43e8-a904-ff9b5d3f5aef}";

  public nsIAutoCompletePopup getPopup();

  public nsIAutoCompleteController getController();

  public boolean getPopupOpen();

  public void setPopupOpen(boolean arg1);

  public boolean getDisableAutoComplete();

  public void setDisableAutoComplete(boolean arg1);

  public boolean getCompleteDefaultIndex();

  public void setCompleteDefaultIndex(boolean arg1);

  public boolean getCompleteSelectedIndex();

  public void setCompleteSelectedIndex(boolean arg1);

  public boolean getForceComplete();

  public void setForceComplete(boolean arg1);

  public long getMinResultsForPopup();

  public void setMinResultsForPopup(long arg1);

  public long getMaxRows();

  public void setMaxRows(long arg1);

  public long getShowCommentColumn();

  public void setShowCommentColumn(long arg1);

  public long getTimeout();

  public void setTimeout(long arg1);

  public String getSearchParam();

  public void setSearchParam(String arg1);

  public long getSearchCount();

  public String getSearchAt(long arg1);

  public String getTextValue();

  public void setTextValue(String arg1);

  public int getSelectionStart();

  public int getSelectionEnd();

  public void selectTextRange(int arg1, int arg2);

  public void onSearchComplete();

  public boolean onTextEntered();

  public boolean onTextReverted();

}
