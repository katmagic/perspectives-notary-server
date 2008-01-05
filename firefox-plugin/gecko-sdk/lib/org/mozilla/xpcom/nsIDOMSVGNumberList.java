/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGNumberList">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGNumberList extends nsISupports
{
  public static final String NS_IDOMSVGNUMBERLIST_IID =
    "{59364ec4-faf1-460f-bf58-e6a6a2769a3a}";

  public long getNumberOfItems();

  public void clear();

  public nsIDOMSVGNumber initialize(nsIDOMSVGNumber arg1);

  public nsIDOMSVGNumber getItem(long arg1);

  public nsIDOMSVGNumber insertItemBefore(nsIDOMSVGNumber arg1, long arg2);

  public nsIDOMSVGNumber replaceItem(nsIDOMSVGNumber arg1, long arg2);

  public nsIDOMSVGNumber removeItem(long arg1);

  public nsIDOMSVGNumber appendItem(nsIDOMSVGNumber arg1);

}
