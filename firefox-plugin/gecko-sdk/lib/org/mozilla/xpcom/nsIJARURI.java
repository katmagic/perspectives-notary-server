/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJARURI">
 **/

package org.mozilla.xpcom;

public interface nsIJARURI extends nsIURL
{
  public static final String NS_IJARURI_IID =
    "{c7e410d3-85f2-11d3-9f63-006008a6efe9}";

  public nsIURI getJARFile();

  public void setJARFile(nsIURI arg1);

  public String getJAREntry();

  public void setJAREntry(String arg1);

}
