/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableMethod">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableMethodInfo extends nsISupports
{
  public static final String NS_ISCRIPTABLEMETHODINFO_IID =
    "{9228afa2-187c-4feb-9228-5108e640ca33}";

  public boolean getIsGetter();

  public boolean getIsSetter();

  public boolean getIsNotXPCOM();

  public boolean getIsConstructor();

  public boolean getIsHidden();

  public String getName();

  public short getParamCount();

  public nsIScriptableParamInfo getParam(short arg1);

  public nsIScriptableParamInfo getResult();

}
