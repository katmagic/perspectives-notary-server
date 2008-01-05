/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIResumableChannel">
 **/

package org.mozilla.xpcom;

public interface nsIResumableChannel extends nsISupports
{
  public static final String NS_IRESUMABLECHANNEL_IID =
    "{4ad136fa-83af-4a22-a76e-503642c0f4a8}";

  public void resumeAt(double arg1, String arg2);

  public String getEntityID();

}
