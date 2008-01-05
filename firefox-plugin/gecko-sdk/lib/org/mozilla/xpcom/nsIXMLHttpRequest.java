/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXMLHttpRequest">
 **/

package org.mozilla.xpcom;

public interface nsIXMLHttpRequest extends nsISupports
{
  public static final String NS_IXMLHTTPREQUEST_IID =
    "{7b3b3c62-9d53-4abc-bc89-c33ce78f439f}";

  public nsIChannel getChannel();

  public nsIDOMDocument getResponseXML();

  public String getResponseText();

  public long getStatus();

  public String getStatusText();

  public void abort();

  public String getAllResponseHeaders();

  public String getResponseHeader(String arg1);

  public void open(String arg1, String arg2);

  public void send(nsIVariant arg1);

  public void setRequestHeader(String arg1, String arg2);

  public int getReadyState();

  public void overrideMimeType(String arg1);

  public boolean getMultipart();

  public void setMultipart(boolean arg1);

}
