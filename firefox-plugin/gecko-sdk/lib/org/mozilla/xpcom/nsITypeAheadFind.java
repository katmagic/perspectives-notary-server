/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITypeAheadFind">
 **/

package org.mozilla.xpcom;

public interface nsITypeAheadFind extends nsISupports
{
  public static final String NS_ITYPEAHEADFIND_IID =
    "{376da416-e6b3-4bac-98f3-6aa408742751}";

  public static final int FIND_FOUND = 0;

  public static final int FIND_NOTFOUND = 1;

  public static final int FIND_WRAPPED = 2;

  public void init(nsIDocShell arg1);

  public int find(String arg1, boolean arg2);

  public int findNext();

  public int findPrevious();

  public void setDocShell(nsIDocShell arg1);

  public String getSearchString();

  public boolean getFocusLinks();

  public void setFocusLinks(boolean arg1);

  public boolean getCaseSensitive();

  public void setCaseSensitive(boolean arg1);

  public nsIDOMElement getFoundLink();

  public nsIDOMWindow getCurrentWindow();

}
