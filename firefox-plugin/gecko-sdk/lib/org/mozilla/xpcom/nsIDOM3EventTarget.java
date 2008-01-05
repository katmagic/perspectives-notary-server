/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOM3EventTarget">
 **/

package org.mozilla.xpcom;

public interface nsIDOM3EventTarget extends nsISupports
{
  public static final String NS_IDOM3EVENTTARGET_IID =
    "{3e9c01a7-de97-4c3b-8294-b4bd9d7056d1}";

  public void addGroupedEventListener(String arg1, nsIDOMEventListener arg2, boolean arg3, nsIDOMEventGroup arg4);

  public void removeGroupedEventListener(String arg1, nsIDOMEventListener arg2, boolean arg3, nsIDOMEventGroup arg4);

  public boolean canTrigger(String arg1);

  public boolean isRegisteredHere(String arg1);

}
