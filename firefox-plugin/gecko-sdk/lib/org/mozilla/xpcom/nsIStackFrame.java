/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStackFrame">
 **/

package org.mozilla.xpcom;

public interface nsIStackFrame extends nsISupports
{
  public static final String NS_ISTACKFRAME_IID =
    "{91d82105-7c62-4f8b-9779-154277c0ee90}";

  public long getLanguage();

  public String getLanguageName();

  public String getFilename();

  public String getName();

  public int getLineNumber();

  public String getSourceLine();

  public nsIStackFrame getCaller();

  public String toString();

}
