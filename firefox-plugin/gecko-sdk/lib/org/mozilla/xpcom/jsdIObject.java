/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIObject">
 **/

package org.mozilla.xpcom;

public interface jsdIObject extends nsISupports
{
  public static final String JSDIOBJECT_IID =
    "{d500e8b8-1dd1-11b2-89a1-cdf55d91cbbd}";

  public String getCreatorURL();

  public long getCreatorLine();

  public String getConstructorURL();

  public long getConstructorLine();

  public jsdIValue getValue();

}
