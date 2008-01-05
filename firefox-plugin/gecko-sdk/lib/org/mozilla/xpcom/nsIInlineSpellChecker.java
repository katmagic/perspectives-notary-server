/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInlineSpellCheck">
 **/

package org.mozilla.xpcom;

public interface nsIInlineSpellChecker extends nsISupports
{
  public static final String NS_IINLINESPELLCHECKER_IID =
    "{f5d1ec9e-4d30-11d8-8053-da0cc7df1f20}";

  public nsIEditorSpellCheck getSpellChecker();

  public boolean getEnableRealTimeSpell();

  public void setEnableRealTimeSpell(boolean arg1);

  public void spellCheckAfterEditorChange(int arg1, nsISelection arg2, nsIDOMNode arg3, int arg4, nsIDOMNode arg5, int arg6, nsIDOMNode arg7, int arg8);

  public void spellCheckRange(nsIDOMRange arg1);

  public nsIDOMRange getMispelledWord(nsIDOMNode arg1, int arg2);

  public void replaceWord(nsIDOMNode arg1, int arg2, String arg3);

  public void addWordToDictionary(String arg1);

  public void ignoreWord(String arg1);

  public void ignoreWords(String[] arg1, long arg2);

}
