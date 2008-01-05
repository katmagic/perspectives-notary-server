/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleHyperL">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleHyperLink extends nsISupports
{
  public static final String NS_IACCESSIBLEHYPERLINK_IID =
    "{a492c7d6-1dd1-11b2-9bc0-80614884799a}";

  public int getAnchors();

  public int getStartIndex();

  public int getEndIndex();

  public nsIURI getURI(int arg1);

  public nsIAccessible getObject(int arg1);

  public boolean isValid();

  public boolean isSelected();

}
