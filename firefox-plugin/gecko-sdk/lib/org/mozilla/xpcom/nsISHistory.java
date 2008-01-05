/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHistory">
 **/

package org.mozilla.xpcom;

public interface nsISHistory extends nsISupports
{
  public static final String NS_ISHISTORY_IID =
    "{7294fe9b-14d8-11d5-9882-00c04fa02f40}";

  public int getCount();

  public int getIndex();

  public int getMaxLength();

  public void setMaxLength(int arg1);

  public nsIHistoryEntry getEntryAtIndex(int arg1, boolean arg2);

  public void purgeHistory(int arg1);

  public void addSHistoryListener(nsISHistoryListener arg1);

  public void removeSHistoryListener(nsISHistoryListener arg1);

  public nsISimpleEnumerator getSHistoryEnumerator();

}
