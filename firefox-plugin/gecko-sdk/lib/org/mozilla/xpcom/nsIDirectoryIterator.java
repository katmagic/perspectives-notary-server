/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirectoryIterato">
 **/

package org.mozilla.xpcom;

public interface nsIDirectoryIterator extends nsISupports
{
  public static final String NS_IDIRECTORYITERATOR_IID =
    "{d8c0a083-0868-11d3-915f-d9d889d48e3c}";

  public void init(nsIFileSpec arg1, boolean arg2);

  public boolean exists();

  public void next();

  public nsIFileSpec getCurrentSpec();

}
