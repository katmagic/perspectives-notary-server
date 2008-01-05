/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXMLDocument">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXMLDocument extends nsIDOMDocument
{
  public static final String NS_IDOMXMLDOCUMENT_IID =
    "{8816d003-e7c8-4065-8827-829b8d07b6e0}";

  public boolean getAsync();

  public void setAsync(boolean arg1);

  public boolean load(String arg1);

  public nsIDOMRange evaluateFIXptr(String arg1);

  public nsIXPointerResult evaluateXPointer(String arg1);

}
