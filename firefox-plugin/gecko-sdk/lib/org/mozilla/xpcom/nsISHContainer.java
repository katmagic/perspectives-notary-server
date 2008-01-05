/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHContainer">
 **/

package org.mozilla.xpcom;

public interface nsISHContainer extends nsISupports
{
  public static final String NS_ISHCONTAINER_IID =
    "{65281ba2-988a-11d3-bdc7-0050040a9b44}";

  public int getChildCount();

  public void addChild(nsISHEntry arg1, int arg2);

  public void removeChild(nsISHEntry arg1);

  public nsISHEntry getChildAt(int arg1);

}
