/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFDataSource">
 **/

package org.mozilla.xpcom;

public interface nsIRDFDataSource extends nsISupports
{
  public static final String NS_IRDFDATASOURCE_IID =
    "{0f78da58-8321-11d2-8eac-00805f29f370}";

  public String getURI();

  public nsIRDFResource getSource(nsIRDFResource arg1, nsIRDFNode arg2, boolean arg3);

  public nsISimpleEnumerator getSources(nsIRDFResource arg1, nsIRDFNode arg2, boolean arg3);

  public nsIRDFNode getTarget(nsIRDFResource arg1, nsIRDFResource arg2, boolean arg3);

  public nsISimpleEnumerator getTargets(nsIRDFResource arg1, nsIRDFResource arg2, boolean arg3);

  public void assert_(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFNode arg3, boolean arg4);

  public void unassert(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFNode arg3);

  public void change(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFNode arg3, nsIRDFNode arg4);

  public void move(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFResource arg3, nsIRDFNode arg4);

  public boolean hasAssertion(nsIRDFResource arg1, nsIRDFResource arg2, nsIRDFNode arg3, boolean arg4);

  public void addObserver(nsIRDFObserver arg1);

  public void removeObserver(nsIRDFObserver arg1);

  public nsISimpleEnumerator arcLabelsIn(nsIRDFNode arg1);

  public nsISimpleEnumerator arcLabelsOut(nsIRDFResource arg1);

  public nsISimpleEnumerator getAllResources();

  public boolean isCommandEnabled(nsISupportsArray arg1, nsIRDFResource arg2, nsISupportsArray arg3);

  public void doCommand(nsISupportsArray arg1, nsIRDFResource arg2, nsISupportsArray arg3);

  public nsISimpleEnumerator getAllCmds(nsIRDFResource arg1);

  public boolean hasArcIn(nsIRDFNode arg1, nsIRDFResource arg2);

  public boolean hasArcOut(nsIRDFResource arg1, nsIRDFResource arg2);

  public void beginUpdateBatch();

  public void endUpdateBatch();

}
