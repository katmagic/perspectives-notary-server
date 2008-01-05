/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULTreeBuilder">
 **/

package org.mozilla.xpcom;

public interface nsIXULTreeBuilder extends nsISupports
{
  public static final String NS_IXULTREEBUILDER_IID =
    "{06b31b15-ebf5-4e74-a0e2-6bc0a18a3969}";

  public nsIRDFResource getResourceAtIndex(int arg1);

  public int getIndexOfResource(nsIRDFResource arg1);

  public void addObserver(nsIXULTreeBuilderObserver arg1);

  public void removeObserver(nsIXULTreeBuilderObserver arg1);

  public void sort(nsIDOMElement arg1);

}
