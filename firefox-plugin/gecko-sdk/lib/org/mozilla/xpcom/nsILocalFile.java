/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsILocalFile">
 **/

package org.mozilla.xpcom;

public interface nsILocalFile extends nsIFile
{
  public static final String NS_ILOCALFILE_IID =
    "{aa610f20-a889-11d3-8c81-000064657374}";

  public void initWithPath(String arg1);

  public void initWithFile(nsILocalFile arg1);

  public boolean getFollowLinks();

  public void setFollowLinks(boolean arg1);

  public long getDiskSpaceAvailable();

  public void appendRelativePath(String arg1);

  public String getPersistentDescriptor();

  public void setPersistentDescriptor(String arg1);

  public void reveal();

  public void launch();

  public String getRelativeDescriptor(nsILocalFile arg1);

  public void setRelativeDescriptor(nsILocalFile arg1, String arg2);

}
