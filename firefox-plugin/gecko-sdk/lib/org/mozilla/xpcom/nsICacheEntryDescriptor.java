/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheEntryDescri">
 **/

package org.mozilla.xpcom;

public interface nsICacheEntryDescriptor extends nsICacheEntryInfo
{
  public static final String NS_ICACHEENTRYDESCRIPTOR_IID =
    "{49c1a11d-f5d2-4f09-8262-551e64908ada}";

  public void setExpirationTime(long arg1);

  public void setDataSize(long arg1);

  public nsIInputStream openInputStream(long arg1);

  public nsIOutputStream openOutputStream(long arg1);

  public nsISupports getCacheElement();

  public void setCacheElement(nsISupports arg1);

  public int getAccessGranted();

  public int getStoragePolicy();

  public void setStoragePolicy(int arg1);

  public nsIFile getFile();

  public nsISupports getSecurityInfo();

  public void setSecurityInfo(nsISupports arg1);

  public void doom();

  public void doomAndFailPendingRequests(long arg1);

  public void markValid();

  public void close();

  public String getMetaDataElement(String arg1);

  public void setMetaDataElement(String arg1, String arg2);

  public void visitMetaData(nsICacheMetaDataVisitor arg1);

}
