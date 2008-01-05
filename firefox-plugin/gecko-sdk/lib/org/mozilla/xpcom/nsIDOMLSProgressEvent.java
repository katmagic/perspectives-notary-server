/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSProgressEve">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSProgressEvent extends nsIDOMEvent
{
  public static final String NS_IDOMLSPROGRESSEVENT_IID =
    "{b9a2371f-70e9-4657-b0e8-28e15b40857e}";

  public nsIDOMLSInput getInput();

  public long getPosition();

  public long getTotalSize();

}
