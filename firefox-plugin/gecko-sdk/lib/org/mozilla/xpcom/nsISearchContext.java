/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISearchContext">
 **/

package org.mozilla.xpcom;

public interface nsISearchContext extends nsISupports
{
  public static final String NS_ISEARCHCONTEXT_IID =
    "{31aba0f0-2d93-11d3-8069-00600811a9c3}";

  public String getSearchString();

  public void setSearchString(String arg1);

  public String getReplaceString();

  public void setReplaceString(String arg1);

  public boolean getSearchBackwards();

  public void setSearchBackwards(boolean arg1);

  public boolean getCaseSensitive();

  public void setCaseSensitive(boolean arg1);

  public boolean getWrapSearch();

  public void setWrapSearch(boolean arg1);

  public nsIDOMWindowInternal getTargetWindow();

  public nsIDOMWindowInternal getFindDialog();

  public void setFindDialog(nsIDOMWindowInternal arg1);

  public nsIDOMWindowInternal getReplaceDialog();

  public void setReplaceDialog(nsIDOMWindowInternal arg1);

}
