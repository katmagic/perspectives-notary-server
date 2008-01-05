/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFastLoadReadCont">
 **/

package org.mozilla.xpcom;

public interface nsIFastLoadReadControl extends nsIFastLoadFileControl
{
  public static final String NS_IFASTLOADREADCONTROL_IID =
    "{652ecec6-d40b-45b6-afef-641d6c63a35b}";

  public long computeChecksum();

  public nsISimpleEnumerator getDependencies();

}
