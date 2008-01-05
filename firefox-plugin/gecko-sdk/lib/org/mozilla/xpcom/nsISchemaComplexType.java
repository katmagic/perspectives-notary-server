/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaComplexTyp">
 **/

package org.mozilla.xpcom;

public interface nsISchemaComplexType extends nsISchemaType
{
  public static final String NS_ISCHEMACOMPLEXTYPE_IID =
    "{3c14a028-6f4e-11d5-9b46-000064657374}";

  public static final int CONTENT_MODEL_EMPTY = 1;

  public static final int CONTENT_MODEL_SIMPLE = 2;

  public static final int CONTENT_MODEL_ELEMENT_ONLY = 3;

  public static final int CONTENT_MODEL_MIXED = 4;

  public static final int DERIVATION_EXTENSION_SIMPLE = 1;

  public static final int DERIVATION_RESTRICTION_SIMPLE = 2;

  public static final int DERIVATION_EXTENSION_COMPLEX = 3;

  public static final int DERIVATION_RESTRICTION_COMPLEX = 4;

  public static final int DERIVATION_SELF_CONTAINED = 5;

  public int getContentModel();

  public int getDerivation();

  public nsISchemaType getBaseType();

  public nsISchemaSimpleType getSimpleBaseType();

  public nsISchemaModelGroup getModelGroup();

  public long getAttributeCount();

  public nsISchemaAttributeComponent getAttributeByIndex(long arg1);

  public nsISchemaAttributeComponent getAttributeByName(String arg1);

  public boolean getAbstract();

  public boolean getIsArray();

  public nsISchemaType getArrayType();

  public long getArrayDimension();

}
