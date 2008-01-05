/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpAuthenticato">
 **/

package org.mozilla.xpcom;

public interface nsIHttpAuthenticator extends nsISupports
{
  public static final String NS_IHTTPAUTHENTICATOR_IID =
    "{0f331436-8bc8-4c68-a124-d0253a19d06f}";

  public static final long REQUEST_BASED = 1L;

  public static final long CONNECTION_BASED = 2L;

  public static final long REUSABLE_CREDENTIALS = 4L;

  public static final long REUSABLE_CHALLENGE = 8L;

  public static final long IDENTITY_IGNORED = 1024L;

  public static final long IDENTITY_INCLUDES_DOMAIN = 2048L;

  public void challengeReceived(nsIHttpChannel arg1, String arg2, boolean arg3, nsISupports[] arg4, nsISupports[] arg5, boolean[] arg6);

  public String generateCredentials(nsIHttpChannel arg1, String arg2, boolean arg3, String arg4, String arg5, String arg6, nsISupports[] arg7, nsISupports[] arg8);

  public long getAuthFlags();

}
