/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFContainer">
 **/

package org.mozilla.xpcom;

public interface nsIRDFContainer extends nsISupports
{
  public static final String NS_IRDFCONTAINER_IID =
    "{d4214e90-fb94-11d2-bdd8-00104bde6048}";

  public nsIRDFDataSource getDataSource();

  public nsIRDFResource getResource();

  public void init(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public int getCount();

  public nsISimpleEnumerator getElements();

  public void appendElement(nsIRDFNode arg1);

  public void removeElement(nsIRDFNode arg1, boolean arg2);

  public void insertElementAt(nsIRDFNode arg1, int arg2, boolean arg3);

  public nsIRDFNode removeElementAt(int arg1, boolean arg2);

  public int indexOf(nsIRDFNode arg1);

}
