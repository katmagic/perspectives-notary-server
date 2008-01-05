/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableDataTy">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableDataType extends nsISupports
{
  public static final String NS_ISCRIPTABLEDATATYPE_IID =
    "{312e3b94-dc98-4ccc-b2fb-e3406f905cc6}";

  public boolean getIsPointer();

  public boolean getIsUniquePointer();

  public boolean getIsReference();

  public boolean getIsArithmetic();

  public boolean getIsInterfacePointer();

  public boolean getIsArray();

  public boolean getIsDependent();

  public int getDataType();

}
