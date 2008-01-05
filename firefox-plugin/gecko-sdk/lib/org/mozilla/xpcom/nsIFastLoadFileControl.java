/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFastLoadFileCont">
 **/

package org.mozilla.xpcom;

public interface nsIFastLoadFileControl extends nsISupports
{
  public static final String NS_IFASTLOADFILECONTROL_IID =
    "{8a1e2c63-af50-4147-af7e-26289dc180dd}";

  public long getChecksum();

  public void setChecksum(long arg1);

  public void startMuxedDocument(nsISupports arg1, String arg2);

  public nsISupports selectMuxedDocument(nsISupports arg1);

  public void endMuxedDocument(nsISupports arg1);

  public boolean hasMuxedDocument(String arg1);

}
