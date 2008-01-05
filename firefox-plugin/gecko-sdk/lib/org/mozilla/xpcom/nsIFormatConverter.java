/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFormatConverter">
 **/

package org.mozilla.xpcom;

public interface nsIFormatConverter extends nsISupports
{
  public static final String NS_IFORMATCONVERTER_IID =
    "{948a0023-e3a7-11d2-96cf-0060b0fb9956}";

  public nsISupportsArray getInputDataFlavors();

  public nsISupportsArray getOutputDataFlavors();

  public boolean canConvert(String arg1, String arg2);

  public void convert(String arg1, nsISupports arg2, long arg3, String arg4, nsISupports[] arg5, long[] arg6);

}
