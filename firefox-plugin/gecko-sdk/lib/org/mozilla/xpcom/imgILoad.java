/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgILoad">
 **/

package org.mozilla.xpcom;

public interface imgILoad extends nsISupports
{
  public static final String IMGILOAD_IID =
    "{e6273acc-1dd1-11b2-a08b-824ad1b1628d}";

  public imgIContainer getImage();

  public void setImage(imgIContainer arg1);

  public boolean getIsMultiPartChannel();

}
