/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGPointList">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGPointList extends nsISupports
{
  public static final String NS_IDOMSVGPOINTLIST_IID =
    "{4c12af24-0fc2-4fe7-b71d-5d6b41d463c1}";

  public long getNumberOfItems();

  public void clear();

  public nsIDOMSVGPoint initialize(nsIDOMSVGPoint arg1);

  public nsIDOMSVGPoint getItem(long arg1);

  public nsIDOMSVGPoint insertItemBefore(nsIDOMSVGPoint arg1, long arg2);

  public nsIDOMSVGPoint replaceItem(nsIDOMSVGPoint arg1, long arg2);

  public nsIDOMSVGPoint removeItem(long arg1);

  public nsIDOMSVGPoint appendItem(nsIDOMSVGPoint arg1);

}
