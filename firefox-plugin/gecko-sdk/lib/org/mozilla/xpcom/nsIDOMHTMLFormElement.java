/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLFormEleme">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLFormElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLFORMELEMENT_IID =
    "{a6cf908f-15b3-11d2-932e-00805f8add32}";

  public nsIDOMHTMLCollection getElements();

  public int getLength();

  public String getName();

  public void setName(String arg1);

  public String getAcceptCharset();

  public void setAcceptCharset(String arg1);

  public String getAction();

  public void setAction(String arg1);

  public String getEnctype();

  public void setEnctype(String arg1);

  public String getMethod();

  public void setMethod(String arg1);

  public String getTarget();

  public void setTarget(String arg1);

  public void submit();

  public void reset();

}
