/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULButtonElem">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULButtonElement extends nsIDOMXULLabeledControlElement
{
  public static final String NS_IDOMXULBUTTONELEMENT_IID =
    "{6852d9a6-1dd2-11b2-a29d-cd7977a91b1b}";

  public static final short CHECKSTATE_UNCHECKED = 0;

  public static final short CHECKSTATE_CHECKED = 1;

  public static final short CHECKSTATE_MIXED = 2;

  public String getType();

  public void setType(String arg1);

  public String getDlgType();

  public void setDlgType(String arg1);

  public boolean getOpen();

  public void setOpen(boolean arg1);

  public boolean getChecked();

  public void setChecked(boolean arg1);

  public int getCheckState();

  public void setCheckState(int arg1);

  public boolean getAutoCheck();

  public void setAutoCheck(boolean arg1);

  public String getGroup();

  public void setGroup(String arg1);

}
