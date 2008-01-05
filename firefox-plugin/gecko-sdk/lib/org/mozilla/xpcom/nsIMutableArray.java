/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMutableArray">
 **/

package org.mozilla.xpcom;

public interface nsIMutableArray extends nsIArray
{
  public static final String NS_IMUTABLEARRAY_IID =
    "{af059da0-c85b-40ec-af07-ae4bfdc192cc}";

  public void appendElement(nsISupports arg1, boolean arg2);

  public void removeElementAt(long arg1);

  public void insertElementAt(nsISupports arg1, long arg2, boolean arg3);

  public void replaceElementAt(nsISupports arg1, long arg2, boolean arg3);

  public void clear();

}
