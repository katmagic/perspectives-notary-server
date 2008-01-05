/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIOSChromeItem">
 **/

package org.mozilla.xpcom;

public interface nsIOSChromeItem extends nsISupports
{
  public static final String NS_IOSCHROMEITEM_IID =
    "{ddd6790a-1dd1-11b2-a804-b522643903b9}";

  public String getName();

  public boolean getHidden();

  public void setHidden(boolean arg1);

  public int getX();

  public int getY();

  public int getWidth();

  public int getHeight();

}
