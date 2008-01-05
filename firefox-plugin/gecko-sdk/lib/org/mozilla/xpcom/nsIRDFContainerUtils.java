/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFContainerUtil">
 **/

package org.mozilla.xpcom;

public interface nsIRDFContainerUtils extends nsISupports
{
  public static final String NS_IRDFCONTAINERUTILS_IID =
    "{d4214e91-fb94-11d2-bdd8-00104bde6048}";

  public boolean isOrdinalProperty(nsIRDFResource arg1);

  public nsIRDFResource indexToOrdinalResource(int arg1);

  public int ordinalResourceToIndex(nsIRDFResource arg1);

  public boolean isContainer(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public boolean isEmpty(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public boolean isBag(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public boolean isSeq(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public boolean isAlt(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public nsIRDFContainer makeBag(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public nsIRDFContainer makeSeq(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public nsIRDFContainer makeAlt(nsIRDFDataSource arg1, nsIRDFResource arg2);

  public int indexOf(nsIRDFDataSource arg1, nsIRDFResource arg2, nsIRDFNode arg3);

}
