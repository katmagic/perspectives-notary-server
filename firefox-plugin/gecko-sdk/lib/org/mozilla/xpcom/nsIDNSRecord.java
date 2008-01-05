/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDNSRecord">
 **/

package org.mozilla.xpcom;

public interface nsIDNSRecord extends nsISupports
{
  public static final String NS_IDNSRECORD_IID =
    "{31c9c52e-1100-457d-abac-d2729e43f506}";

  public String getCanonicalName();

  public String getNextAddrAsString();

  public boolean hasMore();

  public void rewind();

}
