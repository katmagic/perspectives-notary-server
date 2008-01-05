/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfileChangeSta">
 **/

package org.mozilla.xpcom;

public interface nsIProfileChangeStatus extends nsISupports
{
  public static final String NS_IPROFILECHANGESTATUS_IID =
    "{2f977d43-5485-11d4-87e2-0010a4e75ef2}";

  public void vetoChange();

  public void changeFailed();

}
