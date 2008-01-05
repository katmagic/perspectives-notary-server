/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableRegion">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableRegion extends nsISupports
{
  public static final String NS_ISCRIPTABLEREGION_IID =
    "{82d8f400-5bde-11d3-b033-b27a62766bbc}";

  public void init();

  public void setToRegion(nsIScriptableRegion arg1);

  public void setToRect(int arg1, int arg2, int arg3, int arg4);

  public void intersectRegion(nsIScriptableRegion arg1);

  public void intersectRect(int arg1, int arg2, int arg3, int arg4);

  public void unionRegion(nsIScriptableRegion arg1);

  public void unionRect(int arg1, int arg2, int arg3, int arg4);

  public void subtractRegion(nsIScriptableRegion arg1);

  public void subtractRect(int arg1, int arg2, int arg3, int arg4);

  public boolean isEmpty();

  public boolean isEqualRegion(nsIScriptableRegion arg1);

  public void getBoundingBox(int[] arg1, int[] arg2, int[] arg3, int[] arg4);

  public void offset(int arg1, int arg2);

  public boolean containsRect(int arg1, int arg2, int arg3, int arg4);

}
