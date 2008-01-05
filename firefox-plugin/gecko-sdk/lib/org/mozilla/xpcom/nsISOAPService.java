/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPService">
 **/

package org.mozilla.xpcom;

public interface nsISOAPService extends nsISupports
{
  public static final String NS_ISOAPSERVICE_IID =
    "{9927fa40-1dd1-11b2-a8d1-857ad21b872c}";

  public nsISupports getConfiguration();

  public void setConfiguration(nsISupports arg1);

  public boolean process(nsISOAPMessage arg1, nsISOAPResponseListener arg2);

}
