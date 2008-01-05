/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIContentViewer">
 **/

package org.mozilla.xpcom;

public interface nsIContentViewer extends nsISupports
{
  public static final String NS_ICONTENTVIEWER_IID =
    "{6a7ddb40-8a9e-4576-8ad1-71c5641d8780}";

  public nsISupports getContainer();

  public void setContainer(nsISupports arg1);

  public void loadStart(nsISupports arg1);

  public void loadComplete(long arg1);

  public boolean permitUnload();

  public void pageHide(boolean arg1);

  public void close(nsISHEntry arg1);

  public void destroy();

  public void stop();

  public nsIDOMDocument getDOMDocument();

  public void setDOMDocument(nsIDOMDocument arg1);

  public void move(int arg1, int arg2);

  public void show();

  public void hide();

  public boolean getEnableRendering();

  public void setEnableRendering(boolean arg1);

  public boolean getSticky();

  public void setSticky(boolean arg1);

  public boolean requestWindowClose();

  public void open(nsISupports arg1);

  public void clearHistoryEntry();

}
