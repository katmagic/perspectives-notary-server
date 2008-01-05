/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICiter">
 **/

package org.mozilla.xpcom;

public interface nsICiter extends nsISupports
{
  public static final String NS_ICITER_IID =
    "{a6cf9102-15b3-11d2-932e-00805f8add32}";

  public String getCiteString(String arg1);

  public String stripCites(String arg1);

  public String rewrap(String arg1, long arg2, long arg3, boolean arg4);

}
