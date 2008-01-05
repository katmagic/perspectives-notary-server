/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFRemoteDataSou">
 **/

package org.mozilla.xpcom;

public interface nsIRDFRemoteDataSource extends nsISupports
{
  public static final String NS_IRDFREMOTEDATASOURCE_IID =
    "{1d297320-27f7-11d3-be01-000064657374}";

  public boolean getLoaded();

  public void init(String arg1);

  public void refresh(boolean arg1);

  public void flush();

  public void flushTo(String arg1);

}
