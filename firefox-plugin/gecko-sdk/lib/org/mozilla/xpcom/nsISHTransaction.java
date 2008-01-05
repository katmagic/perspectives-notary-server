/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHTransaction">
 **/

package org.mozilla.xpcom;

public interface nsISHTransaction extends nsISupports
{
  public static final String NS_ISHTRANSACTION_IID =
    "{2edf705f-d252-4971-9f09-71dd0f760dc6}";

  public nsISHEntry getSHEntry();

  public void setSHEntry(nsISHEntry arg1);

  public nsISHTransaction getPrev();

  public void setPrev(nsISHTransaction arg1);

  public nsISHTransaction getNext();

  public void setNext(nsISHTransaction arg1);

  public boolean getPersist();

  public void setPersist(boolean arg1);

  public void create(nsISHEntry arg1, nsISHTransaction arg2);

}
