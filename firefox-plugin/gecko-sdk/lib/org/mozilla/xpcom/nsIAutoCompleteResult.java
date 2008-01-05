/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAutoCompleteResu">
 **/

package org.mozilla.xpcom;

public interface nsIAutoCompleteResult extends nsISupports
{
  public static final String NS_IAUTOCOMPLETERESULT_IID =
    "{eb43e1dc-2060-4d8e-aebf-3efec4e21cf8}";

  public static final int RESULT_IGNORED = 1;

  public static final int RESULT_FAILURE = 2;

  public static final int RESULT_NOMATCH = 3;

  public static final int RESULT_SUCCESS = 4;

  public String getSearchString();

  public int getSearchResult();

  public int getDefaultIndex();

  public String getErrorDescription();

  public long getMatchCount();

  public String getValueAt(int arg1);

  public String getCommentAt(int arg1);

  public String getStyleAt(int arg1);

  public void removeValueAt(int arg1, boolean arg2);

}
