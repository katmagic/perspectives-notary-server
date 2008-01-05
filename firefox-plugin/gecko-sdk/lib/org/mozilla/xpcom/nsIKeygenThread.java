/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIKeygenThread">
 **/

package org.mozilla.xpcom;

public interface nsIKeygenThread extends nsISupports
{
  public static final String NS_IKEYGENTHREAD_IID =
    "{8712a243-5539-447c-9f47-8653f40c3a09}";

  public void startKeyGeneration(nsIObserver arg1);

  public void userCanceled(boolean[] arg1);

}
