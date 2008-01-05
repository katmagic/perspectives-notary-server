/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransferable">
 **/

package org.mozilla.xpcom;

public interface nsITransferable extends nsISupports
{
  public static final String NS_ITRANSFERABLE_IID =
    "{8b5314bc-db01-11d2-96ce-0060b0fb9956}";

  public static final int kFlavorHasDataProvider = 0;

  public nsISupportsArray flavorsTransferableCanExport();

  public void getTransferData(String arg1, nsISupports[] arg2, long[] arg3);

  public void getAnyTransferData(String[] arg1, nsISupports[] arg2, long[] arg3);

  public boolean isLargeDataSet();

  public nsISupportsArray flavorsTransferableCanImport();

  public void setTransferData(String arg1, nsISupports arg2, long arg3);

  public void addDataFlavor(String arg1);

  public void removeDataFlavor(String arg1);

  public nsIFormatConverter getConverter();

  public void setConverter(nsIFormatConverter arg1);

}
