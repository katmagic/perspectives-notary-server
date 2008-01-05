/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICertTree">
 **/

package org.mozilla.xpcom;

public interface nsICertTree extends nsITreeView
{
  public static final String NS_ICERTTREE_IID =
    "{4ea60761-31d6-491d-9e34-4b53a26c416c}";

  public void loadCerts(long arg1);

  public void loadCertsFromCache(nsINSSCertCache arg1, long arg2);

  public nsIX509Cert getCert(long arg1);

  public void removeCert(long arg1);

}
