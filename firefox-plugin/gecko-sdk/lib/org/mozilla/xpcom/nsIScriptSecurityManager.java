/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptSecurityMa">
 **/

package org.mozilla.xpcom;

public interface nsIScriptSecurityManager extends nsIXPCSecurityManager
{
  public static final String NS_ISCRIPTSECURITYMANAGER_IID =
    "{f4d74511-2b2d-4a14-a3e4-a392ac5ac3ff}";

  public static final long STANDARD = 0L;

  public static final long DISALLOW_FROM_MAIL = 1L;

  public static final long ALLOW_CHROME = 2L;

  public static final long DISALLOW_SCRIPT_OR_DATA = 4L;

  public static final long DISALLOW_SCRIPT = 8L;

  public void checkLoadURI(nsIURI arg1, nsIURI arg2, long arg3);

  public void checkLoadURIStr(String arg1, String arg2, long arg3);

  public boolean isCapabilityEnabled(String arg1);

  public void enableCapability(String arg1);

  public void revertCapability(String arg1);

  public void disableCapability(String arg1);

  public void setCanEnableCapability(String arg1, String arg2, short arg3);

  public void checkSameOriginURI(nsIURI arg1, nsIURI arg2);

}
