/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserFindIn">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserFindInFrames extends nsISupports
{
  public static final String NS_IWEBBROWSERFINDINFRAMES_IID =
    "{e0f5d182-34bc-11d5-be5b-b760676c6ebc}";

  public nsIDOMWindow getCurrentSearchFrame();

  public void setCurrentSearchFrame(nsIDOMWindow arg1);

  public nsIDOMWindow getRootSearchFrame();

  public void setRootSearchFrame(nsIDOMWindow arg1);

  public boolean getSearchSubframes();

  public void setSearchSubframes(boolean arg1);

  public boolean getSearchParentFrames();

  public void setSearchParentFrames(boolean arg1);

}
