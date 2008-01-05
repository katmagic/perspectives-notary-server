/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocShell">
 **/

package org.mozilla.xpcom;

public interface nsIDocShell extends nsISupports
{
  public static final String NS_IDOCSHELL_IID =
    "{9f0c7461-b9a4-47f6-b88c-421dce1bce66}";

  public static final int INTERNAL_LOAD_FLAGS_NONE = 0;

  public static final int INTERNAL_LOAD_FLAGS_INHERIT_OWNER = 1;

  public static final int INTERNAL_LOAD_FLAGS_DONT_SEND_REFERRER = 2;

  public static final int ENUMERATE_FORWARDS = 0;

  public static final int ENUMERATE_BACKWARDS = 1;

  public static final long APP_TYPE_UNKNOWN = 0L;

  public static final long APP_TYPE_MAIL = 1L;

  public static final long APP_TYPE_EDITOR = 2L;

  public static final long BUSY_FLAGS_NONE = 0L;

  public static final long BUSY_FLAGS_BUSY = 1L;

  public static final long BUSY_FLAGS_BEFORE_PAGE_LOAD = 2L;

  public static final long BUSY_FLAGS_PAGE_LOADING = 4L;

  public static final long LOAD_CMD_NORMAL = 1L;

  public static final long LOAD_CMD_RELOAD = 2L;

  public static final long LOAD_CMD_HISTORY = 4L;

  public void createLoadInfo(nsIDocShellLoadInfo[] arg1);

  public void prepareForNewContentModel();

  public void setCurrentURI(nsIURI arg1);

  public nsIContentViewer getContentViewer();

  public nsIChromeEventHandler getChromeEventHandler();

  public void setChromeEventHandler(nsIChromeEventHandler arg1);

  public nsIDocumentCharsetInfo getDocumentCharsetInfo();

  public void setDocumentCharsetInfo(nsIDocumentCharsetInfo arg1);

  public boolean getAllowPlugins();

  public void setAllowPlugins(boolean arg1);

  public boolean getAllowJavascript();

  public void setAllowJavascript(boolean arg1);

  public boolean getAllowMetaRedirects();

  public void setAllowMetaRedirects(boolean arg1);

  public boolean getAllowSubframes();

  public void setAllowSubframes(boolean arg1);

  public boolean getAllowImages();

  public void setAllowImages(boolean arg1);

  public nsISimpleEnumerator getDocShellEnumerator(int arg1, int arg2);

  public long getAppType();

  public void setAppType(long arg1);

  public boolean getAllowAuth();

  public void setAllowAuth(boolean arg1);

  public float getZoom();

  public void setZoom(float arg1);

  public int getMarginWidth();

  public void setMarginWidth(int arg1);

  public int getMarginHeight();

  public void setMarginHeight(int arg1);

  public boolean getHasFocus();

  public void setHasFocus(boolean arg1);

  public boolean getCanvasHasFocus();

  public void setCanvasHasFocus(boolean arg1);

  public void tabToTreeOwner(boolean arg1, boolean[] arg2);

  public long getBusyFlags();

  public long getLoadType();

  public void setLoadType(long arg1);

  public boolean isBeingDestroyed();

  public boolean getIsExecutingOnLoadHandler();

  public nsISupports getLayoutHistoryState();

  public void setLayoutHistoryState(nsISupports arg1);

  public boolean getShouldSaveLayoutState();

  public nsISecureBrowserUI getSecurityUI();

  public void setSecurityUI(nsISecureBrowserUI arg1);

  public void suspendRefreshURIs();

  public void resumeRefreshURIs();

  public void beginRestore(nsIContentViewer arg1, boolean arg2);

  public void finishRestore();

  public boolean getRestoringDocument();

  public boolean getUseErrorPages();

  public void setUseErrorPages(boolean arg1);

  public int getPreviousTransIndex();

  public int getLoadedTransIndex();

  public void historyPurged(int arg1);

}
