/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMJSWindow">
 **/

package org.mozilla.xpcom;

public interface nsIDOMJSWindow extends nsISupports
{
  public static final String NS_IDOMJSWINDOW_IID =
    "{c8188620-1dd1-11b2-bc88-df8440498add}";

  public void dump(String arg1);

  public int setTimeout();

  public int setInterval();

  public void clearTimeout();

  public void clearInterval();

  public void setResizable(boolean arg1);

  public void captureEvents(int arg1);

  public void releaseEvents(int arg1);

  public void routeEvent(nsIDOMEvent arg1);

  public void enableExternalCapture();

  public void disableExternalCapture();

  public String prompt();

  public nsIDOMWindow open();

  public nsIDOMWindow openDialog();

  public nsIDOMWindow getFrames();

  public boolean find();

}
