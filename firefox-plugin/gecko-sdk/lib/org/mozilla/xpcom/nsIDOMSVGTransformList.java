/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGTransformL">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGTransformList extends nsISupports
{
  public static final String NS_IDOMSVGTRANSFORMLIST_IID =
    "{df41474c-a4f8-4ec3-ae79-4342e6f56d8e}";

  public long getNumberOfItems();

  public void clear();

  public nsIDOMSVGTransform initialize(nsIDOMSVGTransform arg1);

  public nsIDOMSVGTransform getItem(long arg1);

  public nsIDOMSVGTransform insertItemBefore(nsIDOMSVGTransform arg1, long arg2);

  public nsIDOMSVGTransform replaceItem(nsIDOMSVGTransform arg1, long arg2);

  public nsIDOMSVGTransform removeItem(long arg1);

  public nsIDOMSVGTransform appendItem(nsIDOMSVGTransform arg1);

  public nsIDOMSVGTransform createSVGTransformFromMatrix(nsIDOMSVGMatrix arg1);

  public nsIDOMSVGTransform consolidate();

  public nsIDOMSVGMatrix getConsolidationMatrix();

}
