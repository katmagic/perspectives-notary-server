/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIContextMenuListe">
 **/

package org.mozilla.xpcom;

public interface nsIContextMenuListener extends nsISupports
{
  public static final String NS_ICONTEXTMENULISTENER_IID =
    "{3478b6b0-3875-11d4-94ef-0020183bf181}";

  public static final long CONTEXT_NONE = 0L;

  public static final long CONTEXT_LINK = 1L;

  public static final long CONTEXT_IMAGE = 2L;

  public static final long CONTEXT_DOCUMENT = 4L;

  public static final long CONTEXT_TEXT = 8L;

  public static final long CONTEXT_INPUT = 16L;

  public void onShowContextMenu(long arg1, nsIDOMEvent arg2, nsIDOMNode arg3);

}
