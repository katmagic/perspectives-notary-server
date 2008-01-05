/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRelativeFilePref">
 **/

package org.mozilla.xpcom;

public interface nsIRelativeFilePref extends nsISupports
{
  public static final String NS_IRELATIVEFILEPREF_IID =
    "{2f977d4e-5485-11d4-87e2-0010a4e75ef2}";

  public nsILocalFile getFile();

  public void setFile(nsILocalFile arg1);

  public String getRelativeToKey();

  public void setRelativeToKey(String arg1);

}
