/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaRestrictio">
 **/

package org.mozilla.xpcom;

public interface nsISchemaRestrictionType extends nsISchemaSimpleType
{
  public static final String NS_ISCHEMARESTRICTIONTYPE_IID =
    "{3c14a027-6f4e-11d5-9b46-000064657374}";

  public nsISchemaSimpleType getBaseType();

  public long getFacetCount();

  public nsISchemaFacet getFacet(long arg1);

}
