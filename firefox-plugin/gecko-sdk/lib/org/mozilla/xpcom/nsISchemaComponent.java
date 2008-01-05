/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaComponent">
 **/

package org.mozilla.xpcom;

public interface nsISchemaComponent extends nsISupports
{
  public static final String NS_ISCHEMACOMPONENT_IID =
    "{5caaa64e-e191-11d8-842a-000393b6661a}";

  public String getTargetNamespace();

  public void resolve(nsIWebServiceErrorHandler arg1);

  public void clear();

}
