/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleAction">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleAction extends nsISupports
{
  public static final String NS_IACCESSIBLEACTION_IID =
    "{829b36d4-125a-4279-abc4-87d834664f82}";

  public int getActions();

  public boolean doAction(int arg1);

  public String getDescription(int arg1);

  public String getDescriptionConst(int arg1);

  public String getKeyBinding(int arg1);

  public String getKeyBindingConst(int arg1);

}
