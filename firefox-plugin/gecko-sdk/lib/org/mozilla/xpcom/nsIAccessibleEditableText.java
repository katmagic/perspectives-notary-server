/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleEditab">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleEditableText extends nsISupports
{
  public static final String NS_IACCESSIBLEEDITABLETEXT_IID =
    "{91f0a56c-11be-47c7-8d02-7c15e00c05f5}";

  public void setAttributes(int arg1, int arg2, nsISupports arg3);

  public void setTextContents(String arg1);

  public void insertText(String arg1, int arg2);

  public void copyText(int arg1, int arg2);

  public void cutText(int arg1, int arg2);

  public void deleteText(int arg1, int arg2);

  public void pasteText(int arg1);

}
