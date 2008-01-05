/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAutoCompleteSear">
 **/

package org.mozilla.xpcom;

public interface nsIAutoCompleteSearch extends nsISupports
{
  public static final String NS_IAUTOCOMPLETESEARCH_IID =
    "{de8db85f-c1de-4d87-94ba-7844890f91fe}";

  public void startSearch(String arg1, String arg2, nsIAutoCompleteResult arg3, nsIAutoCompleteObserver arg4);

  public void stopSearch();

}
