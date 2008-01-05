/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirIndexParser">
 **/

package org.mozilla.xpcom;

public interface nsIDirIndexParser extends nsIStreamListener
{
  public static final String NS_IDIRINDEXPARSER_IID =
    "{38e3066c-1dd2-11b2-9b59-8be515c1ee3f}";

  public nsIDirIndexListener getListener();

  public void setListener(nsIDirIndexListener arg1);

  public String getComment();

  public String getEncoding();

  public void setEncoding(String arg1);

}
