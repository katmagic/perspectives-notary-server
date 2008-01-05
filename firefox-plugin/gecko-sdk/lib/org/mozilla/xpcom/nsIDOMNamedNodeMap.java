/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNamedNodeMap">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNamedNodeMap extends nsISupports
{
  public static final String NS_IDOMNAMEDNODEMAP_IID =
    "{a6cf907b-15b3-11d2-932e-00805f8add32}";

  public nsIDOMNode getNamedItem(String arg1);

  public nsIDOMNode setNamedItem(nsIDOMNode arg1);

  public nsIDOMNode removeNamedItem(String arg1);

  public nsIDOMNode item(long arg1);

  public long getLength();

  public nsIDOMNode getNamedItemNS(String arg1, String arg2);

  public nsIDOMNode setNamedItemNS(nsIDOMNode arg1);

  public nsIDOMNode removeNamedItemNS(String arg1, String arg2);

}
