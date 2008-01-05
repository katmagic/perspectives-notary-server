/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGPathSegLis">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGPathSegList extends nsISupports
{
  public static final String NS_IDOMSVGPATHSEGLIST_IID =
    "{94a6db98-3f34-4529-a35f-89ef49713795}";

  public long getNumberOfItems();

  public void clear();

  public nsIDOMSVGPathSeg initialize(nsIDOMSVGPathSeg arg1);

  public nsIDOMSVGPathSeg getItem(long arg1);

  public nsIDOMSVGPathSeg insertItemBefore(nsIDOMSVGPathSeg arg1, long arg2);

  public nsIDOMSVGPathSeg replaceItem(nsIDOMSVGPathSeg arg1, long arg2);

  public nsIDOMSVGPathSeg removeItem(long arg1);

  public nsIDOMSVGPathSeg appendItem(nsIDOMSVGPathSeg arg1);

}
