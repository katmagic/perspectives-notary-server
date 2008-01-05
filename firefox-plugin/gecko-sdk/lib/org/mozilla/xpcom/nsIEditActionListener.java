/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditActionListen">
 **/

package org.mozilla.xpcom;

public interface nsIEditActionListener extends nsISupports
{
  public static final String NS_IEDITACTIONLISTENER_IID =
    "{b22907b1-ee93-11d2-8d50-000064657374}";

  public void willCreateNode(String arg1, nsIDOMNode arg2, int arg3);

  public void didCreateNode(String arg1, nsIDOMNode arg2, nsIDOMNode arg3, int arg4, long arg5);

  public void willInsertNode(nsIDOMNode arg1, nsIDOMNode arg2, int arg3);

  public void didInsertNode(nsIDOMNode arg1, nsIDOMNode arg2, int arg3, long arg4);

  public void willDeleteNode(nsIDOMNode arg1);

  public void didDeleteNode(nsIDOMNode arg1, long arg2);

  public void willSplitNode(nsIDOMNode arg1, int arg2);

  public void didSplitNode(nsIDOMNode arg1, int arg2, nsIDOMNode arg3, long arg4);

  public void willJoinNodes(nsIDOMNode arg1, nsIDOMNode arg2, nsIDOMNode arg3);

  public void didJoinNodes(nsIDOMNode arg1, nsIDOMNode arg2, nsIDOMNode arg3, long arg4);

  public void willInsertText(nsIDOMCharacterData arg1, int arg2, String arg3);

  public void didInsertText(nsIDOMCharacterData arg1, int arg2, String arg3, long arg4);

  public void willDeleteText(nsIDOMCharacterData arg1, int arg2, int arg3);

  public void didDeleteText(nsIDOMCharacterData arg1, int arg2, int arg3, long arg4);

  public void willDeleteSelection(nsISelection arg1);

  public void didDeleteSelection(nsISelection arg1);

}
