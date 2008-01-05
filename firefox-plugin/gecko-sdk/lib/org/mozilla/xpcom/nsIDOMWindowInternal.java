/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMWindowInterna">
 **/

package org.mozilla.xpcom;

public interface nsIDOMWindowInternal extends nsIDOMWindow2
{
  public static final String NS_IDOMWINDOWINTERNAL_IID =
    "{f914492c-0138-4123-a634-6ef8e3f126f8}";

  public nsIDOMWindowInternal getWindow();

  public nsIDOMWindowInternal getSelf();

  public nsIDOMNavigator getNavigator();

  public nsIDOMScreen getScreen();

  public nsIDOMHistory getHistory();

  public nsIDOMWindow getContent();

  public nsIDOMBarProp getMenubar();

  public nsIDOMBarProp getToolbar();

  public nsIDOMBarProp getLocationbar();

  public nsIDOMBarProp getPersonalbar();

  public nsIDOMBarProp getStatusbar();

  public nsIDOMBarProp getDirectories();

  public boolean getClosed();

  public nsIDOMCrypto getCrypto();

  public nsIDOMPkcs11 getPkcs11();

  public nsIControllers getControllers();

  public nsIDOMWindowInternal getOpener();

  public void setOpener(nsIDOMWindowInternal arg1);

  public String getStatus();

  public void setStatus(String arg1);

  public String getDefaultStatus();

  public void setDefaultStatus(String arg1);

  public nsIDOMLocation getLocation();

  public int getInnerWidth();

  public void setInnerWidth(int arg1);

  public int getInnerHeight();

  public void setInnerHeight(int arg1);

  public int getOuterWidth();

  public void setOuterWidth(int arg1);

  public int getOuterHeight();

  public void setOuterHeight(int arg1);

  public int getScreenX();

  public void setScreenX(int arg1);

  public int getScreenY();

  public void setScreenY(int arg1);

  public int getPageXOffset();

  public int getPageYOffset();

  public int getScrollMaxX();

  public int getScrollMaxY();

  public long getLength();

  public boolean getFullScreen();

  public void setFullScreen(boolean arg1);

  public void alert(String arg1);

  public boolean confirm(String arg1);

  public String prompt(String arg1, String arg2, String arg3, long arg4);

  public void focus();

  public void blur();

  public void back();

  public void forward();

  public void home();

  public void stop();

  public void print();

  public void moveTo(int arg1, int arg2);

  public void moveBy(int arg1, int arg2);

  public void resizeTo(int arg1, int arg2);

  public void resizeBy(int arg1, int arg2);

  public void scroll(int arg1, int arg2);

  public void close();

  public void updateCommands(String arg1);

  public String atob(String arg1);

  public String btoa(String arg1);

  public nsIDOMElement getFrameElement();

}
