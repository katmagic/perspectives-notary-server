/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISemanticUnitScan">
 **/

package org.mozilla.xpcom;

public interface nsISemanticUnitScanner extends nsISupports
{
  public static final String NS_ISEMANTICUNITSCANNER_IID =
    "{9f620be4-e535-11d6-b254-00039310a47a}";

  public void start(String arg1);

  public boolean next(String arg1, int arg2, int arg3, boolean arg4, int[] arg5, int[] arg6);

}
