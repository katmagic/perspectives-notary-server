/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFastLoadService">
 **/

package org.mozilla.xpcom;

public interface nsIFastLoadService extends nsISupports
{
  public static final String NS_IFASTLOADSERVICE_IID =
    "{759e475e-0c23-4dbf-b1b8-78c9369e3072}";

  public static final int NS_FASTLOAD_READ = 1;

  public static final int NS_FASTLOAD_WRITE = 2;

  public nsIFile newFastLoadFile(String arg1);

  public nsIObjectInputStream newInputStream(nsIInputStream arg1);

  public nsIObjectOutputStream newOutputStream(nsIOutputStream arg1);

  public nsIObjectInputStream getInputStream();

  public void setInputStream(nsIObjectInputStream arg1);

  public nsIObjectOutputStream getOutputStream();

  public void setOutputStream(nsIObjectOutputStream arg1);

  public nsIFastLoadFileIO getFileIO();

  public void setFileIO(nsIFastLoadFileIO arg1);

  public int getDirection();

  public void startMuxedDocument(nsISupports arg1, String arg2, int arg3);

  public nsISupports selectMuxedDocument(nsISupports arg1);

  public void endMuxedDocument(nsISupports arg1);

  public void addDependency(nsIFile arg1);

  public long computeChecksum(nsIFile arg1, nsIFastLoadReadControl arg2);

  public void cacheChecksum(nsIFile arg1, nsIObjectOutputStream arg2);

  public boolean hasMuxedDocument(String arg1);

}
