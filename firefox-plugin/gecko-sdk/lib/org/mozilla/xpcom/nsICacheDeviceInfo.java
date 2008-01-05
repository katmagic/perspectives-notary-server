/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheDeviceInfo">
 **/

package org.mozilla.xpcom;

public interface nsICacheDeviceInfo extends nsISupports
{
  public static final String NS_ICACHEDEVICEINFO_IID =
    "{31d1c294-1dd2-11b2-be3a-c79230dca297}";

  public String getDescription();

  public String getUsageReport();

  public long getEntryCount();

  public long getTotalSize();

  public long getMaximumSize();

}
