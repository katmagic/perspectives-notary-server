/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDNSService">
 **/

package org.mozilla.xpcom;

public interface nsIDNSService extends nsISupports
{
  public static final String NS_IDNSSERVICE_IID =
    "{5c8ec09d-bfbf-4eaf-8a36-0d84b5c8f35b}";

  public static final long RESOLVE_BYPASS_CACHE = 1L;

  public static final long RESOLVE_CANONICAL_NAME = 2L;

  public nsICancelable asyncResolve(String arg1, long arg2, nsIDNSListener arg3, nsIEventTarget arg4);

  public nsIDNSRecord resolve(String arg1, long arg2);

  public String getMyHostName();

}
