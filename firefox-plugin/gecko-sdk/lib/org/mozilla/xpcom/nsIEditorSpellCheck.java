/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditorSpellCheck">
 **/

package org.mozilla.xpcom;

public interface nsIEditorSpellCheck extends nsISupports
{
  public static final String NS_IEDITORSPELLCHECK_IID =
    "{6088a862-1229-11d9-941d-c035b2e390c6}";

  public void initSpellChecker(nsIEditor arg1, boolean arg2);

  public String getNextMisspelledWord();

  public String getSuggestedWord();

  public boolean checkCurrentWord(String arg1);

  public void replaceWord(String arg1, String arg2, boolean arg3);

  public void ignoreWordAllOccurrences(String arg1);

  public void getPersonalDictionary();

  public String getPersonalDictionaryWord();

  public void addWordToDictionary(String arg1);

  public void removeWordFromDictionary(String arg1);

  public void getDictionaryList(String[][] arg1, long[] arg2);

  public String getCurrentDictionary();

  public void setCurrentDictionary(String arg1);

  public void uninitSpellChecker();

  public void setFilter(nsITextServicesFilter arg1);

  public boolean checkCurrentWordNoSuggest(String arg1);

}
