/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFindService">
 **/

package org.mozilla.xpcom;

public interface nsIFindService extends nsISupports
{
  public static final String NS_IFINDSERVICE_IID =
    "{5060b801-340e-11d5-be5b-b3e063ec6a3c}";

  public String getSearchString();

  public void setSearchString(String arg1);

  public String getReplaceString();

  public void setReplaceString(String arg1);

  public boolean getFindBackwards();

  public void setFindBackwards(boolean arg1);

  public boolean getWrapFind();

  public void setWrapFind(boolean arg1);

  public boolean getEntireWord();

  public void setEntireWord(boolean arg1);

  public boolean getMatchCase();

  public void setMatchCase(boolean arg1);

}
