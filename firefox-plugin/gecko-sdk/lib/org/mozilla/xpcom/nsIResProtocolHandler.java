/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIResProtocolHandl">
 **/

package org.mozilla.xpcom;

public interface nsIResProtocolHandler extends nsIProtocolHandler
{
  public static final String NS_IRESPROTOCOLHANDLER_IID =
    "{067ca872-e947-4bd6-8946-a479cb6ba5dd}";

  public void setSubstitution(String arg1, nsIURI arg2);

  public nsIURI getSubstitution(String arg1);

  public boolean hasSubstitution(String arg1);

  public String resolveURI(nsIURI arg1);

}
