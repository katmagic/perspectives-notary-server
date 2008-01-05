/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMMutationEvent">
 **/

package org.mozilla.xpcom;

public interface nsIDOMMutationEvent extends nsIDOMEvent
{
  public static final String NS_IDOMMUTATIONEVENT_IID =
    "{8e440d86-886a-4e76-9e59-c13b939c9a4b}";

  public static final int MODIFICATION = 1;

  public static final int ADDITION = 2;

  public static final int REMOVAL = 3;

  public nsIDOMNode getRelatedNode();

  public String getPrevValue();

  public String getNewValue();

  public String getAttrName();

  public int getAttrChange();

  public void initMutationEvent(String arg1, boolean arg2, boolean arg3, nsIDOMNode arg4, String arg5, String arg6, String arg7, int arg8);

}
