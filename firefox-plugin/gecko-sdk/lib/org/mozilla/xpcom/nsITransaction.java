/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransaction">
 **/

package org.mozilla.xpcom;

public interface nsITransaction extends nsISupports
{
  public static final String NS_ITRANSACTION_IID =
    "{58e330c1-7b48-11d2-98b9-00805f297d89}";

  public void doTransaction();

  public void undoTransaction();

  public void redoTransaction();

  public boolean getIsTransient();

  public boolean merge(nsITransaction arg1);

}
