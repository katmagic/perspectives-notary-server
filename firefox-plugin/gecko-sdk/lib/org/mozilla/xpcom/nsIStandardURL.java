/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStandardURL">
 **/

package org.mozilla.xpcom;

public interface nsIStandardURL extends nsISupports
{
  public static final String NS_ISTANDARDURL_IID =
    "{8793370a-311f-11d4-9876-00c04fa0cf4a}";

  public static final long URLTYPE_STANDARD = 1L;

  public static final long URLTYPE_AUTHORITY = 2L;

  public static final long URLTYPE_NO_AUTHORITY = 3L;

  public void init(long arg1, int arg2, String arg3, String arg4, nsIURI arg5);

  public boolean getMutable();

  public void setMutable(boolean arg1);

}
