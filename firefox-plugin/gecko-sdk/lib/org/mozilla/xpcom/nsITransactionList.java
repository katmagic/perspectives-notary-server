/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransactionList">
 **/

package org.mozilla.xpcom;

public interface nsITransactionList extends nsISupports
{
  public static final String NS_ITRANSACTIONLIST_IID =
    "{97f863f3-f886-11d4-9d39-0060b0f8baff}";

  public int getNumItems();

  public boolean itemIsBatch(int arg1);

  public nsITransaction getItem(int arg1);

  public int getNumChildrenForItem(int arg1);

  public nsITransactionList getChildListForItem(int arg1);

}
