/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFile">
 **/

package org.mozilla.xpcom;

public interface nsIFile extends nsISupports
{
  public static final String NS_IFILE_IID =
    "{c8c0a080-0868-11d3-915f-d9d889d48e3c}";

  public static final long NORMAL_FILE_TYPE = 0L;

  public static final long DIRECTORY_TYPE = 1L;

  public void append(String arg1);

  public void normalize();

  public void create(long arg1, long arg2);

  public String getLeafName();

  public void setLeafName(String arg1);

  public void copyTo(nsIFile arg1, String arg2);

  public void copyToFollowingLinks(nsIFile arg1, String arg2);

  public void moveTo(nsIFile arg1, String arg2);

  public void remove(boolean arg1);

  public long getPermissions();

  public void setPermissions(long arg1);

  public long getPermissionsOfLink();

  public void setPermissionsOfLink(long arg1);

  public long getLastModifiedTime();

  public void setLastModifiedTime(long arg1);

  public long getLastModifiedTimeOfLink();

  public void setLastModifiedTimeOfLink(long arg1);

  public long getFileSize();

  public void setFileSize(long arg1);

  public long getFileSizeOfLink();

  public String getTarget();

  public String getPath();

  public boolean exists();

  public boolean isWritable();

  public boolean isReadable();

  public boolean isExecutable();

  public boolean isHidden();

  public boolean isDirectory();

  public boolean isFile();

  public boolean isSymlink();

  public boolean isSpecial();

  public void createUnique(long arg1, long arg2);

  public nsIFile clone_();

  public boolean equals(nsIFile arg1);

  public boolean contains(nsIFile arg1, boolean arg2);

  public nsIFile getParent();

  public nsISimpleEnumerator getDirectoryEntries();

}
