/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserSetup">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserSetup extends nsISupports
{
  public static final String NS_IWEBBROWSERSETUP_IID =
    "{f15398a0-8018-11d3-af70-00a024ffc08c}";

  public static final long SETUP_ALLOW_PLUGINS = 1L;

  public static final long SETUP_ALLOW_JAVASCRIPT = 2L;

  public static final long SETUP_ALLOW_META_REDIRECTS = 3L;

  public static final long SETUP_ALLOW_SUBFRAMES = 4L;

  public static final long SETUP_ALLOW_IMAGES = 5L;

  public static final long SETUP_FOCUS_DOC_BEFORE_CONTENT = 6L;

  public static final long SETUP_USE_GLOBAL_HISTORY = 256L;

  public static final long SETUP_IS_CHROME_WRAPPER = 7L;

  public void setProperty(long arg1, long arg2);

}
