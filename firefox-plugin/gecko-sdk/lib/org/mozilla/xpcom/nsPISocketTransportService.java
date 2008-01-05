/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsPISocketTransport">
 **/

package org.mozilla.xpcom;

public interface nsPISocketTransportService extends nsISocketTransportService
{
  public static final String NS_PISOCKETTRANSPORTSERVICE_IID =
    "{6f704e69-a5fb-11d9-8ce8-0011246ecd24}";

  public void init();

  public void shutdown();

  public boolean getAutodialEnabled();

  public void setAutodialEnabled(boolean arg1);

}
