/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULDocument">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULDocument extends nsISupports
{
  public static final String NS_IDOMXULDOCUMENT_IID =
    "{e64bb081-13ba-430e-ab70-73a9f1d3de58}";

  public nsIDOMNode getPopupNode();

  public void setPopupNode(nsIDOMNode arg1);

  public nsIDOMNode getTooltipNode();

  public void setTooltipNode(nsIDOMNode arg1);

  public nsIDOMXULCommandDispatcher getCommandDispatcher();

  public int getWidth();

  public int getHeight();

  public nsIDOMNodeList getElementsByAttribute(String arg1, String arg2);

  public void addBroadcastListenerFor(nsIDOMElement arg1, nsIDOMElement arg2, String arg3);

  public void removeBroadcastListenerFor(nsIDOMElement arg1, nsIDOMElement arg2, String arg3);

  public void persist(String arg1, String arg2);

  public void loadOverlay(String arg1, nsIObserver arg2);

}
