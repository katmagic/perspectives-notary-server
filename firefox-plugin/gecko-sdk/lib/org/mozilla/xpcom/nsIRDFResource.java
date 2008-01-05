/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFResource">
 **/

package org.mozilla.xpcom;

public interface nsIRDFResource extends nsIRDFNode
{
  public static final String NS_IRDFRESOURCE_IID =
    "{fb9686a7-719a-49dc-9107-10dea5739341}";

  public String getValue();

  public String getValueUTF8();

  public void init(String arg1);

  public boolean equalsString(String arg1);

  public nsISupports getDelegate(String arg1, String arg2);

  public void releaseDelegate(String arg1);

}
