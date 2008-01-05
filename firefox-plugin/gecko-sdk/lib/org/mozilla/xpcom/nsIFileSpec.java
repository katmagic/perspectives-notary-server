/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFileSpec">
 **/

package org.mozilla.xpcom;

public interface nsIFileSpec extends nsISupports
{
  public static final String NS_IFILESPEC_IID =
    "{37ef2e71-edef-46c7-acd9-f0b6e0b15083}";

  public void fromFileSpec(nsIFileSpec arg1);

  public String getURLString();

  public void setURLString(String arg1);

  public String getUnixStyleFilePath();

  public void setUnixStyleFilePath(String arg1);

  public String getPersistentDescriptorString();

  public void setPersistentDescriptorString(String arg1);

  public String getNativePath();

  public void setNativePath(String arg1);

  public String getNSPRPath();

  public void error();

  public boolean isValid();

  public boolean failed();

  public String getLeafName();

  public void setLeafName(String arg1);

  public nsIFileSpec getParent();

  public nsIInputStream getInputStream();

  public nsIOutputStream getOutputStream();

  public boolean isChildOf(nsIFileSpec arg1);

  public String getFileContents();

  public void setFileContents(String arg1);

  public void makeUnique();

  public void makeUniqueWithSuggestedName(String arg1);

  public void makeUniqueDir();

  public void makeUniqueDirWithSuggestedName(String arg1);

  public long getModDate();

  public boolean modDateChanged(long arg1);

  public boolean isDirectory();

  public boolean isFile();

  public boolean exists();

  public boolean isHidden();

  public boolean equals(nsIFileSpec arg1);

  public long getFileSize();

  public long getDiskSpaceAvailable();

  public void appendRelativeUnixPath(String arg1);

  public void createDir();

  public void touch();

  public boolean isSymlink();

  public void resolveSymlink();

  public void delete(boolean arg1);

  public void truncate(int arg1);

  public void rename(String arg1);

  public void copyToDir(nsIFileSpec arg1);

  public void moveToDir(nsIFileSpec arg1);

  public void execute(String arg1);

  public void openStreamForReading();

  public void openStreamForWriting();

  public void openStreamForReadingAndWriting();

  public void closeStream();

  public boolean isStreamOpen();

  public boolean eof();

  public int read(String[] arg1, int arg2);

  public void readLine(String[] arg1, int arg2, boolean[] arg3);

  public int write(String arg1, int arg2);

  public void flush();

  public void seek(int arg1);

  public int tell();

  public void endLine();

  public String getUnicodePath();

  public void setUnicodePath(String arg1);

}
