/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULMenuListEl">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULMenuListElement extends nsIDOMXULSelectControlElement
{
  public static final String NS_IDOMXULMENULISTELEMENT_IID =
    "{3d49950e-04f9-4e35-a9a0-ffd51356a674}";

  public boolean getEditable();

  public void setEditable(boolean arg1);

  public boolean getOpen();

  public void setOpen(boolean arg1);

  public String getLabel();

  public String getCrop();

  public void setCrop(String arg1);

  public String getImage();

  public void setImage(String arg1);

  public nsIDOMXULTextBoxElement getInputField();

}
