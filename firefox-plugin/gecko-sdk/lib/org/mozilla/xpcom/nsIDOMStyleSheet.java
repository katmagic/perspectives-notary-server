/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMStyleSheet">
 **/

package org.mozilla.xpcom;

public interface nsIDOMStyleSheet extends nsISupports
{
  public static final String NS_IDOMSTYLESHEET_IID =
    "{a6cf9080-15b3-11d2-932e-00805f8add32}";

  public String getType();

  public boolean getDisabled();

  public void setDisabled(boolean arg1);

  public nsIDOMNode getOwnerNode();

  public nsIDOMStyleSheet getParentStyleSheet();

  public String getHref();

  public String getTitle();

  public nsIDOMMediaList getMedia();

}
