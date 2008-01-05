/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserFind">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserFind extends nsISupports
{
  public static final String NS_IWEBBROWSERFIND_IID =
    "{2f977d44-5485-11d4-87e2-0010a4e75ef2}";

  public boolean findNext();

  public String getSearchString();

  public void setSearchString(String arg1);

  public boolean getFindBackwards();

  public void setFindBackwards(boolean arg1);

  public boolean getWrapFind();

  public void setWrapFind(boolean arg1);

  public boolean getEntireWord();

  public void setEntireWord(boolean arg1);

  public boolean getMatchCase();

  public void setMatchCase(boolean arg1);

  public boolean getSearchFrames();

  public void setSearchFrames(boolean arg1);

}
