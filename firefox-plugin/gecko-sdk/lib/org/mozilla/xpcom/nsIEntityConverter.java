/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEntityConverter">
 **/

package org.mozilla.xpcom;

public interface nsIEntityConverter extends nsISupports
{
  public static final String NS_IENTITYCONVERTER_IID =
    "{d14c7111-55e0-11d3-91d9-00105aa3f7dc}";

  public static final long entityNone = 0L;

  public static final long html40Latin1 = 1L;

  public static final long html40Symbols = 2L;

  public static final long html40Special = 4L;

  public static final long transliterate = 8L;

  public static final long mathml20 = 16L;

  public static final long html32 = 1L;

  public static final long html40 = 7L;

  public static final long entityW3C = 23L;

  public String convertUTF32ToEntity(long arg1, long arg2);

  public String convertToEntity(char arg1, long arg2);

  public String convertToEntities(String arg1, long arg2);

}
