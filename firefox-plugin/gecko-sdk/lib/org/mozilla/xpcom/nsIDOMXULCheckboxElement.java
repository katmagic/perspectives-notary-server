/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULCheckboxEl">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULCheckboxElement extends nsIDOMXULLabeledControlElement
{
  public static final String NS_IDOMXULCHECKBOXELEMENT_IID =
    "{5afaba88-1dd2-11b2-9249-dd65a129d0e4}";

  public static final short CHECKSTATE_UNCHECKED = 0;

  public static final short CHECKSTATE_CHECKED = 1;

  public static final short CHECKSTATE_MIXED = 2;

  public boolean getChecked();

  public void setChecked(boolean arg1);

  public int getCheckState();

  public void setCheckState(int arg1);

  public boolean getAutoCheck();

  public void setAutoCheck(boolean arg1);

}
