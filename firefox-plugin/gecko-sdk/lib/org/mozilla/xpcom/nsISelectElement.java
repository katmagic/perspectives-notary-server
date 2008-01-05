/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelectElement">
 **/

package org.mozilla.xpcom;

public interface nsISelectElement extends nsISupports
{
  public static final String NS_ISELECTELEMENT_IID =
    "{35bd8ed5-5f34-4126-8c4f-38ba01681836}";

  public boolean isOptionDisabled(int arg1);

  public boolean setOptionsSelectedByIndex(int arg1, int arg2, boolean arg3, boolean arg4, boolean arg5, boolean arg6);

  public int getOptionIndex(nsIDOMHTMLOptionElement arg1, int arg2, boolean arg3);

  public boolean getHasOptGroups();

}
