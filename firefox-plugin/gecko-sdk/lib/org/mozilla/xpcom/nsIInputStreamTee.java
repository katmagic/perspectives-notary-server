/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInputStreamTee">
 **/

package org.mozilla.xpcom;

public interface nsIInputStreamTee extends nsIInputStream
{
  public static final String NS_IINPUTSTREAMTEE_IID =
    "{44e8b2c8-1ecb-4a63-8b23-3e3500c34f32}";

  public nsIInputStream getSource();

  public void setSource(nsIInputStream arg1);

  public nsIOutputStream getSink();

  public void setSink(nsIOutputStream arg1);

}
