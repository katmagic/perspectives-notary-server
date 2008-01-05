/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIContextMenuInfo">
 **/

package org.mozilla.xpcom;

public interface nsIContextMenuInfo extends nsISupports
{
  public static final String NS_ICONTEXTMENUINFO_IID =
    "{2f977d56-5485-11d4-87e2-0010a4e75ef2}";

  public nsIDOMEvent getMouseEvent();

  public nsIDOMNode getTargetNode();

  public String getAssociatedLink();

  public imgIContainer getImageContainer();

  public nsIURI getImageSrc();

  public imgIContainer getBackgroundImageContainer();

  public nsIURI getBackgroundImageSrc();

}
