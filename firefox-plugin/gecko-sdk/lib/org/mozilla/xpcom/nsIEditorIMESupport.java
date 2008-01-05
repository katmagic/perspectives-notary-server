/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditorIMESupport">
 **/

package org.mozilla.xpcom;

public interface nsIEditorIMESupport extends nsISupports
{
  public static final String NS_IEDITORIMESUPPORT_IID =
    "{205b3e49-aa58-499e-880b-aacab9dede01}";

  public void endComposition();

  public void forceCompositionEnd();

  public void notifyIMEOnFocus();

  public void notifyIMEOnBlur();

}
