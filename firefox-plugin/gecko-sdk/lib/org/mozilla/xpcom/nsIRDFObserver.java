/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFObserver">
 **/

package org.mozilla.xpcom;

public interface nsIRDFObserver extends nsISupports
{
  public static final String NS_IRDFOBSERVER_IID =
    "{3cc75360-484a-11d2-bc16-00805f912fe7}";

  public void onAssert(nsIRDFDataSource arg1, nsIRDFResource arg2, nsIRDFResource arg3, nsIRDFNode arg4);

  public void onUnassert(nsIRDFDataSource arg1, nsIRDFResource arg2, nsIRDFResource arg3, nsIRDFNode arg4);

  public void onChange(nsIRDFDataSource arg1, nsIRDFResource arg2, nsIRDFResource arg3, nsIRDFNode arg4, nsIRDFNode arg5);

  public void onMove(nsIRDFDataSource arg1, nsIRDFResource arg2, nsIRDFResource arg3, nsIRDFResource arg4, nsIRDFNode arg5);

  public void onBeginUpdateBatch(nsIRDFDataSource arg1);

  public void onEndUpdateBatch(nsIRDFDataSource arg1);

}
