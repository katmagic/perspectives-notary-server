/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRegistry">
 **/

package org.mozilla.xpcom;

public interface nsIRegistry extends nsISupports
{
  public static final String NS_IREGISTRY_IID =
    "{5d41a440-8e37-11d2-8059-00600811a9c3}";

  public static final int None = 0;

  public static final int Users = 1;

  public static final int Common = 2;

  public static final int CurrentUser = 3;

  public static final int ApplicationComponentRegistry = 1;

  public static final int ApplicationRegistry = 2;

  public static final int ApplicationCustomRegistry = -1;

  public static final long String = 1L;

  public static final long Int32 = 2L;

  public static final long Bytes = 3L;

  public static final long File = 4L;

  public void open(nsIFile arg1);

  public void openWellKnownRegistry(int arg1);

  public void flush();

  public boolean isOpen();

  public long addKey(long arg1, String arg2);

  public long getKey(long arg1, String arg2);

  public void removeKey(long arg1, String arg2);

  public String getString(long arg1, String arg2);

  public void setString(long arg1, String arg2, String arg3);

  public String getStringUTF8(long arg1, String arg2);

  public void setStringUTF8(long arg1, String arg2, String arg3);

  public short[] getBytesUTF8(long arg1, String arg2, long[] arg3);

  public void setBytesUTF8(long arg1, String arg2, long arg3, short[] arg4);

  public int getInt(long arg1, String arg2);

  public void setInt(long arg1, String arg2, int arg3);

  public long getLongLong(long arg1, String arg2);

  public void setLongLong(long arg1, String arg2, long[] arg3);

  public long addSubtree(long arg1, String arg2);

  public void removeSubtree(long arg1, String arg2);

  public long getSubtree(long arg1, String arg2);

  public long addSubtreeRaw(long arg1, String arg2);

  public void removeSubtreeRaw(long arg1, String arg2);

  public long getSubtreeRaw(long arg1, String arg2);

  public nsIEnumerator enumerateSubtrees(long arg1);

  public nsIEnumerator enumerateAllSubtrees(long arg1);

  public nsIEnumerator enumerateValues(long arg1);

  public long getValueType(long arg1, String arg2);

  public long getValueLength(long arg1, String arg2);

  public void deleteValue(long arg1, String arg2);

  public short[] escapeKey(short[] arg1, long arg2, long[] arg3);

  public short[] unescapeKey(short[] arg1, long arg2, long[] arg3);

  public String getCurrentUserName();

  public void setCurrentUserName(String arg1);

  public void pack();

}
