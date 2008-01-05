/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebNavigation">
 **/

package org.mozilla.xpcom;

public interface nsIWebNavigation extends nsISupports
{
  public static final String NS_IWEBNAVIGATION_IID =
    "{f5d9e7b0-d930-11d3-b057-00a024ffc08c}";

  public static final long LOAD_FLAGS_MASK = 65535L;

  public static final long LOAD_FLAGS_NONE = 0L;

  public static final long LOAD_FLAGS_IS_REFRESH = 16L;

  public static final long LOAD_FLAGS_IS_LINK = 32L;

  public static final long LOAD_FLAGS_BYPASS_HISTORY = 64L;

  public static final long LOAD_FLAGS_REPLACE_HISTORY = 128L;

  public static final long LOAD_FLAGS_BYPASS_CACHE = 256L;

  public static final long LOAD_FLAGS_BYPASS_PROXY = 512L;

  public static final long LOAD_FLAGS_CHARSET_CHANGE = 1024L;

  public static final long LOAD_FLAGS_STOP_CONTENT = 2048L;

  public static final long LOAD_FLAGS_FROM_EXTERNAL = 4096L;

  public static final long STOP_NETWORK = 1L;

  public static final long STOP_CONTENT = 2L;

  public static final long STOP_ALL = 3L;

  public boolean getCanGoBack();

  public boolean getCanGoForward();

  public void goBack();

  public void goForward();

  public void gotoIndex(int arg1);

  public void loadURI(String arg1, long arg2, nsIURI arg3, nsIInputStream arg4, nsIInputStream arg5);

  public void reload(long arg1);

  public void stop(long arg1);

  public nsIDOMDocument getDocument();

  public nsIURI getCurrentURI();

  public nsIURI getReferringURI();

  public nsISHistory getSessionHistory();

  public void setSessionHistory(nsISHistory arg1);

}
