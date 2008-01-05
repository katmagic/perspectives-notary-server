/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleDocume">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleDocument extends nsISupports
{
  public static final String NS_IACCESSIBLEDOCUMENT_IID =
    "{8781fc88-355f-4439-881f-6504a0a1ceb6}";

  public String getURL();

  public String getTitle();

  public String getMimeType();

  public String getDocType();

  public boolean getIsEditable();

  public nsIDOMDocument getDocument();

  public nsIDOMWindow getWindow();

  public nsIAccessible getCaretAccessible();

  public String getNameSpaceURIForID(short arg1);

  public nsIAccessible getAccessibleInParentChain(nsIDOMNode arg1);

}
