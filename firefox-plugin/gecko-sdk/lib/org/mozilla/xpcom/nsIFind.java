/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFind">
 **/

package org.mozilla.xpcom;

public interface nsIFind extends nsISupports
{
  public static final String NS_IFIND_IID =
    "{75125d55-37ee-4575-b9b5-f33bfa68c2a1}";

  public boolean getFindBackwards();

  public void setFindBackwards(boolean arg1);

  public boolean getCaseSensitive();

  public void setCaseSensitive(boolean arg1);

  public nsISupports getWordBreaker();

  public void setWordBreaker(nsISupports arg1);

  public nsIDOMRange find(String arg1, nsIDOMRange arg2, nsIDOMRange arg3, nsIDOMRange arg4);

}
