/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaAttribute">
 **/

package org.mozilla.xpcom;

public interface nsISchemaAttribute extends nsISchemaAttributeComponent
{
  public static final String NS_ISCHEMAATTRIBUTE_IID =
    "{3c14a02e-6f4e-11d5-9b46-000064657374}";

  public static final int USE_OPTIONAL = 1;

  public static final int USE_PROHIBITED = 2;

  public static final int USE_REQUIRED = 3;

  public nsISchemaSimpleType getType();

  public String getDefaultValue();

  public String getFixedValue();

  public int getUse();

}
