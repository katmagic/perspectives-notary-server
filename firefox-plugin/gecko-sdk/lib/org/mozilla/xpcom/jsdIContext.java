/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIContext">
 **/

package org.mozilla.xpcom;

public interface jsdIContext extends jsdIEphemeral
{
  public static final String JSDICONTEXT_IID =
    "{a2dd25a4-1dd1-11b2-bda6-ed525acd4c35}";

  public static final int OPT_STRICT = 1;

  public static final int OPT_WERR = 2;

  public static final int OPT_VAROBJFIX = 4;

  public static final int OPT_ISUPPORTS = 8;

  public long getOptions();

  public void setOptions(long arg1);

  public int getVersion();

  public void setVersion(int arg1);

  public long getTag();

  public nsISupports getPrivateData();

  public nsISupports getWrappedContext();

  public jsdIValue getGlobalObject();

  public boolean getScriptsEnabled();

  public void setScriptsEnabled(boolean arg1);

}
