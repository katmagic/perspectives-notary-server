/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDialogParamBlock">
 **/

package org.mozilla.xpcom;

public interface nsIDialogParamBlock extends nsISupports
{
  public static final String NS_IDIALOGPARAMBLOCK_IID =
    "{f76c0901-437a-11d3-b7a0-e35db351b4bc}";

  public int getInt(int arg1);

  public void setInt(int arg1, int arg2);

  public void setNumberStrings(int arg1);

  public String getString(int arg1);

  public void setString(int arg1, String arg2);

  public nsIMutableArray getObjects();

  public void setObjects(nsIMutableArray arg1);

}
