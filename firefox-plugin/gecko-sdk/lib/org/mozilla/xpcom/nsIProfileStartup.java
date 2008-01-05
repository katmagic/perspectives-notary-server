/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfileStartup">
 **/

package org.mozilla.xpcom;

public interface nsIProfileStartup extends nsISupports
{
  public static final String NS_IPROFILESTARTUP_IID =
    "{048e5ca1-0eb7-4bb1-a9a2-a36f7d4e0e3c}";

  public nsIFile getDirectory();

  public void doStartup();

}
