/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMRangeExceptio">
 **/

package org.mozilla.xpcom;

public interface nsIDOMRangeException extends nsISupports
{
  public static final String NS_IDOMRANGEEXCEPTION_IID =
    "{0f807301-39d2-11d6-a7f2-8f504ff870dc}";

  public static final int BAD_BOUNDARYPOINTS_ERR = 1;

  public static final int INVALID_NODE_TYPE_ERR = 2;

  public int getCode();

}
