/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDragService">
 **/

package org.mozilla.xpcom;

public interface nsIDragService extends nsISupports
{
  public static final String NS_IDRAGSERVICE_IID =
    "{8b5314bb-db01-11d2-96ce-0060b0fb9956}";

  public static final int DRAGDROP_ACTION_NONE = 0;

  public static final int DRAGDROP_ACTION_COPY = 1;

  public static final int DRAGDROP_ACTION_MOVE = 2;

  public static final int DRAGDROP_ACTION_LINK = 4;

  public void invokeDragSession(nsIDOMNode arg1, nsISupportsArray arg2, nsIScriptableRegion arg3, long arg4);

  public nsIDragSession getCurrentSession();

  public void startDragSession();

  public void endDragSession();

}
