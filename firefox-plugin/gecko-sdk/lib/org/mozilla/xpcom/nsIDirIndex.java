/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirIndex">
 **/

package org.mozilla.xpcom;

public interface nsIDirIndex extends nsISupports
{
  public static final String NS_IDIRINDEX_IID =
    "{23bbabd0-1dd2-11b2-86b7-aad68ae7d7e0}";

  public static final long TYPE_UNKNOWN = 0L;

  public static final long TYPE_DIRECTORY = 1L;

  public static final long TYPE_FILE = 2L;

  public static final long TYPE_SYMLINK = 3L;

  public long getType();

  public void setType(long arg1);

  public String getContentType();

  public void setContentType(String arg1);

  public String getLocation();

  public void setLocation(String arg1);

  public String getDescription();

  public void setDescription(String arg1);

  public long getSize();

  public void setSize(long arg1);

  public double getLastModified();

  public void setLastModified(double arg1);

}
