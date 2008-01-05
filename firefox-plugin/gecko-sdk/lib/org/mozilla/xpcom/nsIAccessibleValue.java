/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleValue">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleValue extends nsISupports
{
  public static final String NS_IACCESSIBLEVALUE_IID =
    "{f4abbc2f-0f28-47dc-a9e9-f7a1719ab2be}";

  public double getMaximumValue();

  public double getMinimumValue();

  public double getCurrentValue();

  public boolean setCurrentValue(double arg1);

}
