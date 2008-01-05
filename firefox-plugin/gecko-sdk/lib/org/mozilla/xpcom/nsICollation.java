/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICollation">
 **/

package org.mozilla.xpcom;

public interface nsICollation extends nsISupports
{
  public static final String NS_ICOLLATION_IID =
    "{b0132cc0-3786-4557-9874-910d7def5f93}";

  public static final int kCollationStrengthDefault = 0;

  public static final int kCollationCaseInsensitiveAscii = 1;

  public static final int kCollationAccentInsenstive = 2;

  public static final int kCollationCaseSensitive = 0;

  public static final int kCollationCaseInSensitive = 3;

  public void initialize(nsILocale arg1);

  public int compareString(int arg1, String arg2, String arg3);

}
