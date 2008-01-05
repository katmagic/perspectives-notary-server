/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableParamI">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableParamInfo extends nsISupports
{
  public static final String NS_ISCRIPTABLEPARAMINFO_IID =
    "{2309482b-4631-455f-833f-5e4e9ce38589}";

  public boolean getIsIn();

  public boolean getIsOut();

  public boolean getIsRetval();

  public boolean getIsShared();

  public boolean getIsDipper();

  public nsIScriptableDataType getType();

}
