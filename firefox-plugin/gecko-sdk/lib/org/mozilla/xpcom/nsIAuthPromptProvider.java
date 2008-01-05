/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAuthPromptProvid">
 **/

package org.mozilla.xpcom;

public interface nsIAuthPromptProvider extends nsISupports
{
  public static final String NS_IAUTHPROMPTPROVIDER_IID =
    "{129d3bd5-8a26-4b0b-b8a0-19fdea029196}";

  public static final long PROMPT_NORMAL = 0L;

  public static final long PROMPT_PROXY = 1L;

  public nsIAuthPrompt getAuthPrompt(long arg1);

}
