/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJSID">
 **/

package org.mozilla.xpcom;

public interface nsIJSID extends nsISupports
{
  public static final String NS_IJSID_IID =
    "{c86ae131-d101-11d2-9841-006008962422}";

  public String getName();

  public String getNumber();

  public boolean getValid();

  public boolean equals(nsIJSID arg1);

  public void initialize(String arg1);

  public String toString();

}
