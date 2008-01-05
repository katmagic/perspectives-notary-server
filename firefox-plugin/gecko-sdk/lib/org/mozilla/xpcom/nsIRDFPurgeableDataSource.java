/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFPurgeableData">
 **/

package org.mozilla.xpcom;

public interface nsIRDFPurgeableDataSource extends nsISupports
{
  public static final String NS_IRDFPURGEABLEDATASOURCE_IID =
    "{951700f0-fed0-11d2-bdd9-00104bde6048}";

  public boolean mark(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFNode arg3, boolean arg4);

  public void sweep();

}
