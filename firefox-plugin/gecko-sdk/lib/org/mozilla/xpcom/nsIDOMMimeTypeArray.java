/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMMimeTypeArray">
 **/

package org.mozilla.xpcom;

public interface nsIDOMMimeTypeArray extends nsISupports
{
  public static final String NS_IDOMMIMETYPEARRAY_IID =
    "{f6134683-f28b-11d2-8360-c90899049c3c}";

  public long getLength();

  public nsIDOMMimeType item(long arg1);

  public nsIDOMMimeType namedItem(String arg1);

}
