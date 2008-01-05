/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXTFElementWrappe">
 **/

package org.mozilla.xpcom;

public interface nsIXTFElementWrapper extends nsISupports
{
  public static final String NS_IXTFELEMENTWRAPPER_IID =
    "{444d0276-3302-4d35-a74e-25c4e9c483c9}";

  public nsIDOMElement getElementNode();

  public nsIDOMElement getDocumentFrameElement();

  public long getNotificationMask();

  public void setNotificationMask(long arg1);

  public void setIntrinsicState(int arg1);

}
