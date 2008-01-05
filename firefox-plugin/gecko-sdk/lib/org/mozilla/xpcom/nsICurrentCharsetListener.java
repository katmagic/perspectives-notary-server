/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICurrentCharsetLi">
 **/

package org.mozilla.xpcom;

public interface nsICurrentCharsetListener extends nsISupports
{
  public static final String NS_ICURRENTCHARSETLISTENER_IID =
    "{cf9428c1-df50-11d3-9d0c-0050040007b2}";

  public void setCurrentCharset(String arg1);

  public void setCurrentMailCharset(String arg1);

  public void setCurrentComposerCharset(String arg1);

}
