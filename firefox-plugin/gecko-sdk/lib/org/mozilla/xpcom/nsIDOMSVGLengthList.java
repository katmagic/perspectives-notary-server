/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGLengthList">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGLengthList extends nsISupports
{
  public static final String NS_IDOMSVGLENGTHLIST_IID =
    "{a8760fcd-3de5-446a-a009-5cf877e7a4df}";

  public long getNumberOfItems();

  public void clear();

  public nsIDOMSVGLength initialize(nsIDOMSVGLength arg1);

  public nsIDOMSVGLength getItem(long arg1);

  public nsIDOMSVGLength insertItemBefore(nsIDOMSVGLength arg1, long arg2);

  public nsIDOMSVGLength replaceItem(nsIDOMSVGLength arg1, long arg2);

  public nsIDOMSVGLength removeItem(long arg1);

  public nsIDOMSVGLength appendItem(nsIDOMSVGLength arg1);

}
