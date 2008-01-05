/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleHyperT">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleHyperText extends nsISupports
{
  public static final String NS_IACCESSIBLEHYPERTEXT_IID =
    "{8f18d922-1dd2-11b2-82ea-829b78a44413}";

  public int getLinks();

  public nsIAccessibleHyperLink getLink(int arg1);

  public int getLinkIndex(int arg1);

  public int getSelectedLinkIndex();

}
