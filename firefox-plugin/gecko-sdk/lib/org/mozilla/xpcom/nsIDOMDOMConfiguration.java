/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDOMConfigurat">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDOMConfiguration extends nsISupports
{
  public static final String NS_IDOMDOMCONFIGURATION_IID =
    "{cfb5b821-9016-4a79-9d98-87b57c3ea0c7}";

  public void setParameter(String arg1, nsIVariant arg2);

  public nsIVariant getParameter(String arg1);

  public boolean canSetParameter(String arg1, nsIVariant arg2);

}
