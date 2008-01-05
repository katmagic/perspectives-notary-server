/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFService">
 **/

package org.mozilla.xpcom;

public interface nsIRDFService extends nsISupports
{
  public static final String NS_IRDFSERVICE_IID =
    "{bfd05261-834c-11d2-8eac-00805f29f370}";

  public nsIRDFResource getResource(String arg1);

  public nsIRDFResource getUnicodeResource(String arg1);

  public nsIRDFResource getAnonymousResource();

  public nsIRDFLiteral getLiteral(String arg1);

  public nsIRDFDate getDateLiteral(long arg1);

  public nsIRDFInt getIntLiteral(int arg1);

  public boolean isAnonymousResource(nsIRDFResource arg1);

  public void registerResource(nsIRDFResource arg1, boolean arg2);

  public void unregisterResource(nsIRDFResource arg1);

  public void registerDataSource(nsIRDFDataSource arg1, boolean arg2);

  public void unregisterDataSource(nsIRDFDataSource arg1);

  public nsIRDFDataSource getDataSource(String arg1);

  public nsIRDFDataSource getDataSourceBlocking(String arg1);

}
