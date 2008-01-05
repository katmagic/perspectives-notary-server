/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheEntryInfo">
 **/

package org.mozilla.xpcom;

public interface nsICacheEntryInfo extends nsISupports
{
  public static final String NS_ICACHEENTRYINFO_IID =
    "{fab51c92-95c3-4468-b317-7de4d7588254}";

  public String getClientID();

  public String getDeviceID();

  public String getKey();

  public int getFetchCount();

  public long getLastFetched();

  public long getLastModified();

  public long getExpirationTime();

  public long getDataSize();

  public boolean isStreamBased();

}
