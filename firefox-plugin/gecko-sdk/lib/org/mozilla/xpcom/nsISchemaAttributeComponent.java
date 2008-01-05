/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaAttributeC">
 **/

package org.mozilla.xpcom;

public interface nsISchemaAttributeComponent extends nsISchemaComponent
{
  public static final String NS_ISCHEMAATTRIBUTECOMPONENT_IID =
    "{3c14a02d-6f4e-11d5-9b46-000064657374}";

  public static final int COMPONENT_TYPE_ATTRIBUTE = 1;

  public static final int COMPONENT_TYPE_GROUP = 2;

  public static final int COMPONENT_TYPE_ANY = 3;

  public String getName();

  public int getComponentType();

}
