/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIFilter">
 **/

package org.mozilla.xpcom;

public interface jsdIFilter extends nsISupports
{
  public static final String JSDIFILTER_IID =
    "{05593438-1b83-4517-864f-3cea3d37a266}";

  public static final long FLAG_RESERVED_MASK = 255L;

  public static final long FLAG_ENABLED = 1L;

  public static final long FLAG_PASS = 2L;

  public long getFlags();

  public void setFlags(long arg1);

  public nsISupports getGlobalObject();

  public void setGlobalObject(nsISupports arg1);

  public String getUrlPattern();

  public void setUrlPattern(String arg1);

  public long getStartLine();

  public void setStartLine(long arg1);

  public long getEndLine();

  public void setEndLine(long arg1);

}
