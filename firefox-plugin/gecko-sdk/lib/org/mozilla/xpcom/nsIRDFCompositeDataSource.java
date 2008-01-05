/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFCompositeData">
 **/

package org.mozilla.xpcom;

public interface nsIRDFCompositeDataSource extends nsIRDFDataSource
{
  public static final String NS_IRDFCOMPOSITEDATASOURCE_IID =
    "{96343820-307c-11d2-bc15-00805f912fe7}";

  public boolean getAllowNegativeAssertions();

  public void setAllowNegativeAssertions(boolean arg1);

  public boolean getCoalesceDuplicateArcs();

  public void setCoalesceDuplicateArcs(boolean arg1);

  public void addDataSource(nsIRDFDataSource arg1);

  public void removeDataSource(nsIRDFDataSource arg1);

  public nsISimpleEnumerator getDataSources();

}
