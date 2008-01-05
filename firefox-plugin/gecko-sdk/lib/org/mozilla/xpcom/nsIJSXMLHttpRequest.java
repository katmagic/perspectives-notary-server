/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJSXMLHttpRequest">
 **/

package org.mozilla.xpcom;

public interface nsIJSXMLHttpRequest extends nsISupports
{
  public static final String NS_IJSXMLHTTPREQUEST_IID =
    "{9deabc90-28d5-41d3-a660-474f2254f4ba}";

  public nsIDOMEventListener getOnload();

  public void setOnload(nsIDOMEventListener arg1);

  public nsIDOMEventListener getOnerror();

  public void setOnerror(nsIDOMEventListener arg1);

  public nsIDOMEventListener getOnprogress();

  public void setOnprogress(nsIDOMEventListener arg1);

  public nsIOnReadyStateChangeHandler getOnreadystatechange();

  public void setOnreadystatechange(nsIOnReadyStateChangeHandler arg1);

}
