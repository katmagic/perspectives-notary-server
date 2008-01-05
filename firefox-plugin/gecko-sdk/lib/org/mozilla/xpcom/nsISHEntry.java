/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHEntry">
 **/

package org.mozilla.xpcom;

public interface nsISHEntry extends nsIHistoryEntry
{
  public static final String NS_ISHENTRY_IID =
    "{542a98b9-2889-4922-aaf4-02b6056f4136}";

  public void setURI(nsIURI arg1);

  public nsIURI getReferrerURI();

  public void setReferrerURI(nsIURI arg1);

  public nsIContentViewer getContentViewer();

  public void setContentViewer(nsIContentViewer arg1);

  public boolean getSticky();

  public void setSticky(boolean arg1);

  public nsISupports getWindowState();

  public void setWindowState(nsISupports arg1);

  public void addChildShell(nsIDocShellTreeItem arg1);

  public nsIDocShellTreeItem childShellAt(int arg1);

  public void clearChildShells();

  public nsISupportsArray getRefreshURIList();

  public void setRefreshURIList(nsISupportsArray arg1);

  public void syncPresentationState();

  public void setTitle(String arg1);

  public nsIInputStream getPostData();

  public void setPostData(nsIInputStream arg1);

  public nsISupports getLayoutHistoryState();

  public void setLayoutHistoryState(nsISupports arg1);

  public nsISHEntry getParent();

  public void setParent(nsISHEntry arg1);

  public long getLoadType();

  public void setLoadType(long arg1);

  public long getID();

  public void setID(long arg1);

  public long getPageIdentifier();

  public void setPageIdentifier(long arg1);

  public nsISupports getCacheKey();

  public void setCacheKey(nsISupports arg1);

  public boolean getSaveLayoutStateFlag();

  public void setSaveLayoutStateFlag(boolean arg1);

  public boolean getExpirationStatus();

  public void setExpirationStatus(boolean arg1);

  public String getContentType();

  public void setContentType(String arg1);

  public void setScrollPosition(int arg1, int arg2);

  public void getScrollPosition(int[] arg1, int[] arg2);

  public void create(nsIURI arg1, String arg2, nsIInputStream arg3, nsISupports arg4, nsISupports arg5, String arg6);

  public nsISHEntry clone_();

  public void setIsSubFrame(boolean arg1);

  public nsIContentViewer getAnyContentViewer(nsISHEntry[] arg1);

}
