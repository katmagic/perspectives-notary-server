/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMAttr">
 **/

package org.mozilla.xpcom;

public interface nsIDOMAttr extends nsIDOMNode
{
  public static final String NS_IDOMATTR_IID =
    "{a6cf9070-15b3-11d2-932e-00805f8add32}";

  public String getName();

  public boolean getSpecified();

  public String getValue();

  public void setValue(String arg1);

  public nsIDOMElement getOwnerElement();

}
