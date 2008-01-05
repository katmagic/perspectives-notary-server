/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULTreeBuilderOb">
 **/

package org.mozilla.xpcom;

public interface nsIXULTreeBuilderObserver extends nsISupports
{
  public static final String NS_IXULTREEBUILDEROBSERVER_IID =
    "{a5480e0d-ac7c-42e5-aca5-d7f0bbffa207}";

  public static final int DROP_BEFORE = -1;

  public static final int DROP_ON = 0;

  public static final int DROP_AFTER = 1;

  public boolean canDrop(int arg1, int arg2);

  public void onDrop(int arg1, int arg2);

  public void onToggleOpenState(int arg1);

  public void onCycleHeader(String arg1, nsIDOMElement arg2);

  public void onCycleCell(int arg1, String arg2);

  public void onSelectionChanged();

  public void onPerformAction(String arg1);

  public void onPerformActionOnRow(String arg1, int arg2);

  public void onPerformActionOnCell(String arg1, int arg2, String arg3);

}
