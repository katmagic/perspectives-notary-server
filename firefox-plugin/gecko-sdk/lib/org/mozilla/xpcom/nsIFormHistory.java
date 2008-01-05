/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFormHistory">
 **/

package org.mozilla.xpcom;

public interface nsIFormHistory extends nsISupports
{
  public static final String NS_IFORMHISTORY_IID =
    "{fa5a871d-29f5-489e-aaa4-c266def52b79}";

  public long getRowCount();

  public void getEntryAt(long arg1, String arg2, String arg3);

  public void getNameAt(long arg1, String arg2);

  public void getValueAt(long arg1, String arg2);

  public void addEntry(String arg1, String arg2);

  public void removeEntryAt(long arg1);

  public void removeEntriesForName(String arg1);

  public void removeAllEntries();

  public boolean nameExists(String arg1);

  public boolean entryExists(String arg1, String arg2);

}
