/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURIFixup">
 **/

package org.mozilla.xpcom;

public interface nsIURIFixup extends nsISupports
{
  public static final String NS_IURIFIXUP_IID =
    "{2efd4a40-a5e1-11d4-9589-0020183bf181}";

  public static final long FIXUP_FLAG_NONE = 0L;

  public static final long FIXUP_FLAG_ALLOW_KEYWORD_LOOKUP = 1L;

  public static final long FIXUP_FLAGS_MAKE_ALTERNATE_URI = 2L;

  public nsIURI createExposableURI(nsIURI arg1);

  public nsIURI createFixupURI(String arg1, long arg2);

}
