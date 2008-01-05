/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableInterf">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableInterfaceInfo extends nsISupports
{
  public static final String NS_ISCRIPTABLEINTERFACEINFO_IID =
    "{f902d5ba-2ef6-444e-8a17-52cb70715c10}";

  public void init(String arg1);

  public void initWithName(String arg1);

  public String getName();

  public String getInterfaceID();

  public boolean getIsValid();

  public boolean getIsScriptable();

  public nsIScriptableInterfaceInfo getParent();

  public int getMethodCount();

  public int getConstantCount();

  public nsIScriptableMethodInfo getMethodInfo(int arg1);

  public nsIScriptableMethodInfo getMethodInfoForName(String arg1, int[] arg2);

  public nsIScriptableConstant getConstant(int arg1);

  public nsIScriptableInterfaceInfo getInfoForParam(int arg1, nsIScriptableParamInfo arg2);

  public String getIIDForParam(int arg1, nsIScriptableParamInfo arg2);

  public nsIScriptableDataType getTypeForParam(int arg1, nsIScriptableParamInfo arg2, int arg3);

  public short getSizeIsArgNumberForParam(int arg1, nsIScriptableParamInfo arg2, int arg3);

  public short getLengthIsArgNumberForParam(int arg1, nsIScriptableParamInfo arg2, int arg3);

  public short getInterfaceIsArgNumberForParam(int arg1, nsIScriptableParamInfo arg2);

  public boolean isIID(String arg1);

  public boolean getIsFunction();

  public boolean hasAncestor(String arg1);

}
