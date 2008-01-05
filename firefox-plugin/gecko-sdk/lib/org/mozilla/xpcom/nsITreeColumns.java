/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITreeColumns">
 **/

package org.mozilla.xpcom;

public interface nsITreeColumns extends nsISupports
{
  public static final String NS_ITREECOLUMNS_IID =
    "{fcc7b6b5-f7d7-4e57-abd1-080602deb21d}";

  public nsITreeBoxObject getTree();

  public int getCount();

  public nsITreeColumn getFirstColumn();

  public nsITreeColumn getLastColumn();

  public nsITreeColumn getPrimaryColumn();

  public nsITreeColumn getSortedColumn();

  public nsITreeColumn getKeyColumn();

  public nsITreeColumn getColumnFor(nsIDOMElement arg1);

  public nsITreeColumn getNamedColumn(String arg1);

  public nsITreeColumn getColumnAt(int arg1);

  public void invalidateColumns();

  public void restoreNaturalOrder();

}
