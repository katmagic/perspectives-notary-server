/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHistoryInternal">
 **/

package org.mozilla.xpcom;

public interface nsISHistoryInternal extends nsISupports
{
  public static final String NS_ISHISTORYINTERNAL_IID =
    "{494fac3c-64f4-41b8-b209-b4ada899613b}";

  public void addEntry(nsISHEntry arg1, boolean arg2);

  public nsISHTransaction getRootTransaction();

  public nsIDocShell getRootDocShell();

  public void setRootDocShell(nsIDocShell arg1);

  public void updateIndex();

  public void replaceEntry(int arg1, nsISHEntry arg2);

  public nsISHistoryListener getListener();

  public void evictContentViewers(int arg1, int arg2);

  public int getHistoryMaxTotalViewers();

}
