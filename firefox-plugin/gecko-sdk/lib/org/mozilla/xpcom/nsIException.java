/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIException">
 **/

package org.mozilla.xpcom;

public interface nsIException extends nsISupports
{
  public static final String NS_IEXCEPTION_IID =
    "{f3a8d3b4-c424-4edc-8bf6-8974c983ba78}";

  public String getMessage();

  public long getResult();

  public String getName();

  public String getFilename();

  public long getLineNumber();

  public long getColumnNumber();

  public nsIStackFrame getLocation();

  public nsIException getInner();

  public nsISupports getData();

  public String toString();

}
