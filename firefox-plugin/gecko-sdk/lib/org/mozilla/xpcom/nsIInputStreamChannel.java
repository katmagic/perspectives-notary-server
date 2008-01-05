/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInputStreamChann">
 **/

package org.mozilla.xpcom;

public interface nsIInputStreamChannel extends nsIChannel
{
  public static final String NS_IINPUTSTREAMCHANNEL_IID =
    "{560a64ce-6d66-44db-b38e-864469c52d03}";

  public void setURI(nsIURI arg1);

  public nsIInputStream getContentStream();

  public void setContentStream(nsIInputStream arg1);

}
