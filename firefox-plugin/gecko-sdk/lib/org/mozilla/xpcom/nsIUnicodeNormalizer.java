/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUnicodeNormalize">
 **/

package org.mozilla.xpcom;

public interface nsIUnicodeNormalizer extends nsISupports
{
  public static final String NS_IUNICODENORMALIZER_IID =
    "{b43a461f-1bcf-4329-820b-66e48c979e14}";

  public void normalizeUnicodeNFD(String arg1, String arg2);

  public void normalizeUnicodeNFC(String arg1, String arg2);

  public void normalizeUnicodeNFKD(String arg1, String arg2);

  public void normalizeUnicodeNFKC(String arg1, String arg2);

}
